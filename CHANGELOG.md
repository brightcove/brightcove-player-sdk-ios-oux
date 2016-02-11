# 2.0.1
### Breaking Changes
* After seeking over an ad, the ad will play, and then the regular video content will play. Previously, after seeking over an ad, the regular video content would play only if it had previously been playing.

### Additions and Improvements
* Fixes an issue where FairPlay-protected content would not play.
* Fixes an issue where controls would show on a post-roll ad.
* Fixes an issue where progress would be reported erratically when seeking over an ad on iOS 8.
* Adds more robust handling of unexpected ad data.

# 2.0.0
### Breaking Changes
* The static library distributable has been removed. If installed manually (not CocoaPods), you will need to remove `libBCOVOUX.a` and its headers from the Header Search Path. Please see README.md for new install options (including a static library framework).
* Header `BCOVOUX.h` has been removed. Please see README.md for new import options.

### Additions and Improvements
* Bitcode support.
* You must use the Brightcove Player SDK for iOS version 5.0.2+.

# 1.0.3
### Additions and Improvements
* Internal Improvements to support Player SDK 4.4.3.

# 1.0.2
### Additions and Improvements
* You must use the Brightcove Player SDK for iOS version 4.4.0+.

# 1.0.1
### Breaking Changes
* This release changes the `oux_seekToTime:` to not replay pre-roll ads when seeking to kCMTimeZero.