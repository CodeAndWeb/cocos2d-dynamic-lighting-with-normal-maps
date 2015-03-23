#import <Foundation/Foundation.h>
#import "CCPackageDownloadManagerDelegate.h"
#import "CCPackageUnzipperDelegate.h"

@class CCPackage;
@protocol CCPackageManagerDelegate;

/** CCPackageManager is the central class of the packages feature. It allows you to download a package, 
 enable/disable an installed package or remove a downloaded package from disk.
 
 The manager provides a delegate property to report progress of the different lifecycle steps of a package. 
 The CCPackageManagerDelegate protocol describes the common interface.

 ### Package Lifecycle
 - **not installed** - The package does not exist within the app or the download has not been started yet.
 - **download** - The package is being downloaded as a zip file from a remote host.
 - **unzip** - Download finished, the zip file is now being unpacked.
 - **install** - The contents of the zip file are copied to the destination (installation) folder.
 - **enabled/disabled** - If the package is enabled its contents become available to a Cocos2D app.
 
 You can find more [technical documentation about packages on the wiki](https://github.com/spritebuilder/SpriteBuilder/wiki/Packages).
 
 @note The CCPackageManager is meant to be used as singleton, use the class method `sharedManager` to get the singleton instance.
 */
@interface CCPackageManager : NSObject <CCPackageDownloadManagerDelegate, CCPackageUnzipperDelegate>

/** @name Accessing the Singleton Instance */

/**
 *  Returns a shared instance of the CCPackageManager, this is the suggested way to use the manager.
 *  @since v3.3 and later
 */
+ (CCPackageManager *)sharedManager;

/** @name Package Manager Delegate */

/**
 *  Package manager's delegate
 *  @since v3.3 and later
 *  @see CCPackageManagerDelegate
 */
@property (nonatomic, weak) id <CCPackageManagerDelegate> delegate;

/** @name Obtaining Installed Packages */

/**
 *  Returns all packages managed by the CCPackageManager
 *  @since v3.3 and later
 */
@property (nonatomic, readonly) NSArray *allPackages;

/**
 *  The path where all installed packages are stored. This path is relative to the caches folder which location is depending
 *  on the OS. Default is "Packages".
 *  @since v3.3 and later
 */
@property (nonatomic, copy) NSString *installRelPath;

/**
 *  Returns a package identified by name. Resolution and OS are determined implicitly.
 *
 *  @param name Name of the package
 *  @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)packageWithName:(NSString *)name;

/**
 *  Returns a package identified by name and resolution. OS is determined implicitly.
 *  Helpful if you are using packages of a different resolution.
 *
 *  @param name Name of the package
 *  @param resolution SpriteBuilder resolution string (ie `phonehd`)
 *  @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)packageWithName:(NSString *)name resolution:(NSString *)resolution;

/**
 *  Returns a package identified by name and resolution.
 *  Helpful if you are using packages of a different resolution and os
 *
 *  @param name Name of the package
 *  @param resolution SpriteBuilder resolution string (ie `phonehd`)
 *  @param os operating system string (ie iOS, Android, Mac)
 *  @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)packageWithName:(NSString *)name resolution:(NSString *)resolution os:(NSString *)os;

/** @name Loading/Saving Packages */

/**
 *  Loads all packages from user defaults. Supposed to be invoked after app finished launching and Cocos2d has been set up.
 *  @since v3.3 and later
 */
- (void)loadPackages;

/**
 *  Persists all packages to user defaults. Save often! It is recommended to at least save packages when receiving the
 `applicationWillTerminate` and `applicationWillEnterBackground` notifications.
 *  @since v3.3 and later
 */
- (void)savePackages;

/** @name Adding/Removing Packages */

/**
 * Adds a package to the package manager. Only packages with status initial can be added.
 *
 * @param package The package to be added to the package manager
 * @since v3.3 and later
 *  @see CCPackage
 */
- (void)addPackage:(CCPackage *)package;

/**
 * Deletes a package.
 * Will disable the package first and delete it from disk. Temp download and unzip files will be removed as well.
 * A package that is being unzipped cannot be deleted. Try after the unzipping finished.
 * The status will become CCPackageStatusDeleted in case you still hold a reference to the object.
 * localDownloURL, unzipURL and installRelURL will be nil after a succesful deletion.
 *
 * @param package The package to be deleted
 * @param error Error pointer with details about a failed operation
 *
 * @return Success(YES) or failure(NO) of the operation
 * @since v3.3 and later
 *  @see CCPackage
 */
- (BOOL)deletePackage:(CCPackage *)package error:(NSError **)error;

/** @name Enable/Disable Packages */

/**
 * Disables a package. Only packages with state CCPackageStatusInstalledEnabled can be disabled.
 * The package is removed from cocos2d's search, sprite sheets and filename lookups are reloaded.
 * Package will be added to managed packages if it was not.
 *
 * @param package The package to be disabled
 * @param error Error pointer with details about a failed operation
 *
 * @return Success(YES) or failure(NO) of the operation
 * @since v3.3 and later
 *  @see CCPackage
 */
- (BOOL)disablePackage:(CCPackage *)package error:(NSError **)error;

/**
 * Enables a package. Only packages with state CCPackageStatusInstalledDisabled can be enabled.
 * Package will be added to managed packages if it was not.
 *
 * The package is added to cocos2d's search, sprite sheets getting loaded as well as filename lookups
 *
 * @param package The package to be enabled
 * @param error Error pointer with details about a failed operation
 *
 * @return Success(YES) or failure(NO) of the operation
 * @since v3.3 and later
 *  @see CCPackage
 */
- (BOOL)enablePackage:(CCPackage *)package error:(NSError **)error;

/** @name Initiating Package Download */

/**
 *  URL used as base to locate packages. A package standard identifier is added to create a full URL.
 *  BaseURL is only used in conjunction with downloadPackageWithName:resolution:enableAfterDownload. More details below.
 *  @since v3.3 and later
 */
@property (nonatomic, copy) NSURL *baseURL;

/**
 * The all inclusive method to add a package to your app.
 * Returns a new package immediately which will be downloaded, unzipped and installed asynchronously to the Packages folder in /Library/Caches (default)
 * OS and resolution are determined implicitly. Resolution is derived from CCFileUtils' searchResolutionsOrder first entry.
 *
 * If a package with the same name and resolution already exists it won't be rescheduled for downloading.
 * If you need to update a package by re-downloading it you will have to delete it first.
 * The various delegate callbacks provide feedback about the current steps of the whole process.
 * You can KVO the package's status property as well, which will change during the cause of the whole process.
 * The URL is determined by the baseURL property and the standard identifier created by the name, os and resolution.
 *
 * Example: base URL being `http://foo` and name: `DLC_Bundle`, os: `iOS` (determined by manager), resolution: `phonehd` results in the following URL: `http://foo/DLC_Bundle-iOS-phonehd.zip`
 *
 * @param name Name of the package
 * @param enableAfterDownload If the package should be enabled in cocos2d after download. You can enable it with the enablePackage: method later on.
 * @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)downloadPackageWithName:(NSString *)name
                   enableAfterDownload:(BOOL)enableAfterDownload;

/**
 * Like the method above. Instead of using the baseURL, name and resolution you can provide the URL directly.
 * Returns a new package immediately which will be downloaded, unzipped and installed asynchronously to the Packages folder in /Library/Caches (default)
 * OS is determined implicitly.
 *
 * @param name Name of the package
 * @param resolution Resolution of the package, e.g. phonehd, tablethd etc.
 * @param enableAfterDownload If the package should be enabled in cocos2d after download. You can enable it with the enablePackage: method later on.
 * @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)downloadPackageWithName:(NSString *)name
                            resolution:(NSString *)resolution
                   enableAfterDownload:(BOOL)enableAfterDownload;

/**
 * Like the method above. Instead of using the baseURL, name and resolution you can provide the URL directly.
 *
 * @param name Name of the package
 * @param resolution Resolution of the package, e.g. phonehd, tablethd etc.
 * @param remoteURL URL of the package to be downloaded
 * @param os operating system of the package to be downloaded
 * @param enableAfterDownload If the package should be enabled in cocos2d after download. You can enable it with the enablePackage: method later on.
 * @since v3.3 and later
 *  @see CCPackage
 */
- (CCPackage *)downloadPackageWithName:(NSString *)name
                            resolution:(NSString *)resolution
                                    os:(NSString *)os
                             remoteURL:(NSURL *)remoteURL
                   enableAfterDownload:(BOOL)enableAfterDownload;

/**
 * Downloads a package. If the package was not managed before it will be added to the managed packages.
 * A download will only start if the status is CCPackageStatusInitial, CCPackageStatusDownloadFailed.
 * A package with status CCPackageStatusDownloadPaused will be resumed if possible.
 *
 * @param package The package to be managed by the package manager
 * @param enableAfterDownload If the package should be enabled in cocos2d after download. You can enable it with the enablePackage: method later on.
 * @since v3.3 and later
 *  @see CCPackage
 */
- (void)downloadPackage:(CCPackage *)package enableAfterDownload:(BOOL)enableAfterDownload;


/** @name Manage Downloads in Progress */

/**
 *  If downloads should be resumed if partial download found
 *  Default is YES
 *  @since v3.3 and later
 */
@property (nonatomic) BOOL resumeDownloads;

/**
 * Cancels the download of a package if the package has one of the following status:
 *    CCPackageStatusDownloadPaused, CCPackageStatusDownloading, CCPackageStatusDownloaded, CCPackageStatusDownloadFailed
 * Status of package is reset to CCPackageStatusInitial.
 *
 * @param package The package which download should be cancelled
 * @since v3.3 and later
 *  @see CCPackage
 */
- (void)cancelDownloadOfPackage:(CCPackage *)package;

/**
 * Pauses the download of a package.
 *
 * @param package The package which download should be paused
 * @since v3.3 and later
 *  @see CCPackage
 */
- (void)pauseDownloadOfPackage:(CCPackage *)package;

/**
 * Resumes the download of a package.
 *
 * @param package The package which download should be resumed
 * @since v3.3 and later
 *  @see CCPackage
 */
- (void)resumeDownloadOfPackage:(CCPackage *)package;

/**
 * Pauses all downloads of packages
 * @since v3.3 and later
 */
- (void)pauseAllDownloads;

/**
 * Resumes all downloads of packages
 * @since v3.3 and later
 */
- (void)resumeAllDownloads;

/** @name Choosing a Dispatch Queue for Unzip Task */

/**
 *  The queue on which unzipping of packages is achieved, default is DISPATCH_QUEUE_PRIORITY_LOW.
 *  On iOS 5.0, MacOS 10.7 and below you have to get rid of the queue after use if it's not a global one.
 *  If set to nil, queue will be reset to default.
 *  @since v3.3 and later
 */
#if OS_OBJECT_HAVE_OBJC_SUPPORT == 1
@property (nonatomic, strong) dispatch_queue_t unzippingQueue;
#else
@property (nonatomic) dispatch_queue_t unzippingQueue;
#endif

@end
