#2.1.2
### Additions and Improvements
* This release adds a dynamic framework that supports tvOS.
* `- (id<BCOVPlaybackController>)createOUXPlaybackController` was added to the `BCOVPlayerSDKManager (BCOVOUXAdditions)` category.
* `- (CMTime)oux_absoluteTimeAtContentTime:(CMTime)contentTime` and `- (CMTime)oux_contentTimeAtAbsoluteTime:(CMTime)absoluteTime` were added to the `BCOVPlayerSDKManager (BCOVOUXAdditions)` category. These methods allow you to convert back and forth between the absolute time (CMTime of the physical video stream including ads) and the content time (CMTime of the logical video stream without ads).
* Fixes an issue where extra `...didEnterAdSequence...` and `...didExitAdSequence...` delegate methods would be called after seeking over midroll ads.

# 2.1.1
### Additions and Improvements
* Deprecated `[BCOVPlayerSDKManager BCOVOUXdefaultControlsViewStrategy]`. Use the PlayerUI controls instead. See the README for full details.
* Internal improvements.

# 2.1.0
### Additions and Improvements

* Internal improvements to support ad controls in the Brightcove PlayerUI.
* Support for disabling ads while seeking forward. Refer to README.md for details.

### Breaking Changes
* You must use the Brightcove Player SDK for iOS version 5.1 or higher.

# 2.0.6
### Additions and Improvements
* Support for VMAP 1.0.1 format ad responses. The Brightcove OnceUX plugin now supports both VMAP 1.0 and VMAP 1.0.1 ad response formats.
* Support for client-side and server-side ad event tracking. Selecting Server-side ad event tracking prevents ad progress events from being tracked through the client.

# 2.0.5
### Additions and Improvements
* When a OnceUX stream stalls due to network slowdowns or interruptions, it can now be restarted using ` [BCOVPlaybackController resumeVideoAtTime:withAutoPlay:]`. Previously, only streams without OnceUX or FairPlay could be restarted.
* Seek speed is improved when not seeking over ads.

# 2.0.4
### Additions and Improvements
* Fixes an issue where seeking due to slider scrubbing would not work reliably.

### Breaking Changes
* This release requires that you use Brightcove Player SDK for iOS version 5.0.3+.

# 2.0.3
### Additions and Improvements
* Fixes an issue where Once ads would not play normally on devices where the Region was set to certain international locales.

# 2.0.2
### Additions and Improvements
* The BCOVPlaybackSession BCOVVideo property now includes cue points to represent the start of each Ad sequence.
* Internal Improvements.

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
