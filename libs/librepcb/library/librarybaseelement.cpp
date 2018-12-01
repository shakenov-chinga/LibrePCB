/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * https://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************************
 *  Includes
 ******************************************************************************/
#include "librarybaseelement.h"

#include "librarybaseelementcheck.h"

#include <librepcb/common/application.h>
#include <librepcb/common/fileio/sexpression.h>
#include <librepcb/common/fileio/transactionalfilesystem.h>
#include <librepcb/common/fileio/versionfile.h>

#include <QtCore>

/*******************************************************************************
 *  Namespace
 ******************************************************************************/
namespace librepcb {
namespace library {

/*******************************************************************************
 *  Constructors / Destructor
 ******************************************************************************/

LibraryBaseElement::LibraryBaseElement(
    bool dirnameMustBeUuid, const QString& shortElementName,
    const QString& longElementName, const Uuid& uuid, const Version& version,
    const QString& author, const ElementName& name_en_US,
    const QString& description_en_US, const QString& keywords_en_US)
  : QObject(nullptr),
    mDirectory(),
    mOpenedReadOnly(false),
    mFileSystem(new TransactionalFileSystem()),
    mDirectoryNameMustBeUuid(dirnameMustBeUuid),
    mShortElementName(shortElementName),
    mLongElementName(longElementName),
    mUuid(uuid),
    mVersion(version),
    mAuthor(author),
    mCreated(QDateTime::currentDateTime()),
    mIsDeprecated(false),
    mNames(name_en_US),
    mDescriptions(description_en_US),
    mKeywords(keywords_en_US) {
}

LibraryBaseElement::LibraryBaseElement(const FilePath& elementDirectory,
                                       bool            dirnameMustBeUuid,
                                       const QString&  shortElementName,
                                       const QString&  longElementName,
                                       bool            readOnly)
  : QObject(nullptr),
    mDirectory(elementDirectory),
    mOpenedReadOnly(readOnly),
    mFileSystem(new TransactionalFileSystem()),
    mDirectoryNameMustBeUuid(dirnameMustBeUuid),
    mShortElementName(shortElementName),
    mLongElementName(longElementName),
    mUuid(Uuid::createRandom()),  // just for initialization, will be
                                  // overwritten
    mVersion(Version::fromString(
        "0.1")),  // just for initialization, will be overwritten
    mNames(ElementName(
        "unknown")),  // just for initialization, will be overwritten
    mDescriptions(""),
    mKeywords("") {
  // open the directory
  mFileSystem->loadFromDirectory(mDirectory);

  // determine the filepath to the version file
  QString versionFileName = ".librepcb-" % mShortElementName;

  // check if the directory is a library element
  if (!mFileSystem->fileExists(versionFileName)) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(tr("Directory is not a library element of type %1: \"%2\""))
            .arg(mLongElementName, mDirectory.toNative()));
  }

  // check directory name
  QString dirUuidStr = mDirectory.getFilename();
  if (mDirectoryNameMustBeUuid && (!Uuid::isValid(dirUuidStr))) {
    throw RuntimeError(__FILE__, __LINE__,
                       QString(tr("Directory name is not a valid UUID: \"%1\""))
                           .arg(mDirectory.toNative()));
  }

  // read version number from version file
  VersionFile versionFile =
      VersionFile::fromByteArray(mFileSystem->readBinary(versionFileName));
  if (versionFile.getVersion() > qApp->getAppVersion()) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(
            tr("The library element %1 was created with a newer application "
               "version. You need at least LibrePCB version %2 to open it."))
            .arg(mDirectory.toNative())
            .arg(versionFile.getVersion().toPrettyStr(3)));
  }

  // open main file
  FilePath sexprFilePath = mDirectory.getPathTo(mLongElementName % ".lp");
  mLoadingFileDocument   = SExpression::parse(
      mFileSystem->readText(sexprFilePath.getFilename()), sexprFilePath);

  // read attributes
  if (mLoadingFileDocument.getChildByIndex(0).isString()) {
    mUuid = mLoadingFileDocument.getChildByIndex(0).getValue<Uuid>();
  } else {
    // backward compatibility, remove this some time!
    mUuid = mLoadingFileDocument.getValueByPath<Uuid>("uuid");
  }
  mVersion      = mLoadingFileDocument.getValueByPath<Version>("version");
  mAuthor       = mLoadingFileDocument.getValueByPath<QString>("author");
  mCreated      = mLoadingFileDocument.getValueByPath<QDateTime>("created");
  mIsDeprecated = mLoadingFileDocument.getValueByPath<bool>("deprecated");

  // read names, descriptions and keywords in all available languages
  mNames        = LocalizedNameMap(mLoadingFileDocument);
  mDescriptions = LocalizedDescriptionMap(mLoadingFileDocument);
  mKeywords     = LocalizedKeywordsMap(mLoadingFileDocument);

  // check if the UUID equals to the directory basename
  if (mDirectoryNameMustBeUuid && (mUuid.toStr() != dirUuidStr)) {
    qDebug() << mUuid.toStr() << "!=" << dirUuidStr;
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(
            tr("UUID mismatch between element directory and main file: \"%1\""))
            .arg(sexprFilePath.toNative()));
  }
}

LibraryBaseElement::~LibraryBaseElement() noexcept {
}

/*******************************************************************************
 *  Getters
 ******************************************************************************/

QStringList LibraryBaseElement::getAllAvailableLocales() const noexcept {
  QStringList list;
  list.append(mNames.keys());
  list.append(mDescriptions.keys());
  list.append(mKeywords.keys());
  list.removeDuplicates();
  list.sort(Qt::CaseSensitive);
  return list;
}

/*******************************************************************************
 *  General Methods
 ******************************************************************************/

LibraryElementCheckMessageList LibraryBaseElement::runChecks() const {
  LibraryBaseElementCheck check(*this);
  return check.runChecks();  // can throw
}

void LibraryBaseElement::save() {
  if (mOpenedReadOnly) {
    throw RuntimeError(
        __FILE__, __LINE__,
        QString(tr("Library element was opened in read-only mode: \"%1\""))
            .arg(mDirectory.toNative()));
  }

  // save S-Expressions file
  QString     sexprFileName = mLongElementName % ".lp";
  SExpression root(serializeToDomElement("librepcb_" % mLongElementName));
  mFileSystem->writeText(sexprFileName, root.toString(0));

  // save version number file
  QString     versionFileName = ".librepcb-" % mShortElementName;
  VersionFile versionFile(qApp->getFileFormatVersion());
  mFileSystem->writeBinary(versionFileName, versionFile.toByteArray());

  // save whole file system
  mFileSystem->saveToDirectory(mDirectory);
}

void LibraryBaseElement::saveTo(const FilePath& destination) {
  // copy to new directory
  copyTo(destination, false);
}

void LibraryBaseElement::saveIntoParentDirectory(const FilePath& parentDir) {
  FilePath elemDir = parentDir.getPathTo(mUuid.toStr());
  saveTo(elemDir);
}

void LibraryBaseElement::moveTo(const FilePath& destination) {
  // copy to new directory and remove source directory
  copyTo(destination, true);
}

void LibraryBaseElement::moveIntoParentDirectory(const FilePath& parentDir) {
  FilePath elemDir = parentDir.getPathTo(mUuid.toStr());
  moveTo(elemDir);
}

/*******************************************************************************
 *  Protected Methods
 ******************************************************************************/

void LibraryBaseElement::cleanupAfterLoadingElementFromFile() noexcept {
  mLoadingFileDocument = SExpression();  // destroy the whole DOM tree
}

void LibraryBaseElement::copyTo(const FilePath& destination,
                                bool            removeSource) {
  if (destination != mDirectory) {
    // check destination directory name validity
    if (mDirectoryNameMustBeUuid &&
        (destination.getFilename() != mUuid.toStr())) {
      throw RuntimeError(
          __FILE__, __LINE__,
          QString(
              tr("Library element directory name is not a valid UUID: \"%1\""))
              .arg(destination.getFilename()));
    }

    // check if destination directory exists already
    if ((destination.isExistingDir() && (!destination.isEmptyDir())) ||
        destination.isExistingFile()) {
      throw RuntimeError(
          __FILE__, __LINE__,
          QString(tr("Could not copy "
                     "library element \"%1\" to \"%2\" because the destination "
                     "exists already."))
              .arg(mDirectory.toNative(), destination.toNative()));
    }

    // copy current directory to destination
    mFileSystem->saveToDirectory(destination);

    // memorize the current directory and change element's directory
    FilePath sourceDir = mDirectory;

    // save the library element to the destination directory
    mDirectory      = destination;
    mOpenedReadOnly = false;
    save();

    // remove source directory if required
    if (removeSource) {
      // FileUtils::removeDirRecursively(sourceDir);
    }
  } else {
    // no copy action required, just save the element
    save();
  }
}

void LibraryBaseElement::serialize(SExpression& root) const {
  root.appendChild(mUuid);
  mNames.serialize(root);
  mDescriptions.serialize(root);
  mKeywords.serialize(root);
  root.appendChild("author", mAuthor, true);
  root.appendChild("version", mVersion, true);
  root.appendChild("created", mCreated, true);
  root.appendChild("deprecated", mIsDeprecated, true);
}

/*******************************************************************************
 *  End of File
 ******************************************************************************/

}  // namespace library
}  // namespace librepcb
