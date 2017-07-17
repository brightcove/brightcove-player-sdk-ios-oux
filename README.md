# Brightcove OnceUX Plugin for Brightcove Player SDK for iOS, version 6.0.2.86

Supported Platforms
===================
iOS 8.0 and above.

tvOS 9.0 and above.

Installation
============
The Brightcove OnceUX for Brightcove Player SDK provides two installation packages for iOS, a static library framework and a dynamic framework.

CocoaPods
--------------

You can use [CocoaPods][cocoapods] to add the OnceUX Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-OnceUX` podspec [here][podspecs].

Static Framework example:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'

pod 'Brightcove-Player-OnceUX'
```
    
Dynamic Framework example:

```
source 'https://github.com/brightcove/BrightcoveSpecs.git'

pod 'Brightcove-Player-OnceUX/dynamic'
```
    
Maintaining an up-to-date master podspec repo is necessary to ensure that you are always using the latest versions of Brightcove software. As of CocoaPods 1.0.0, podspec repo updates are no longer an automatic feature, so to update your master repo, run the following on the command line:

```
pod repo update
```

Manual
--------------

To add the OUX Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
2. Download the latest zip'ed release of the BrightcoveOUX plugin from our [release page][release].
3. Add `BrightcoveOUX.framework` to your project.
4. On the "Build Settings" tab of your application target, ensure that the "Framework Search Paths" include the path to the framework. This should have been done automatically unless the framework is stored under a different root directory than your project.
5. (Dynamic Framework only) On the "General" tab of your application target, add 'BrightcoveOUX.framework' to the "Embedded Binaries" section.
6. (Dynamic Framework only) On the "Build Phases" tab, add a "Run Script" phase with the command `bash ${BUILT_PRODUCTS_DIR}/${FRAMEWORKS_FOLDER_PATH}/BrightcoveOUX.framework/strip-frameworks.sh`. Check "Run script only when installing". This will remove unneeded architectures from the build, which is important for App Store submission.
7. (Static Framework only) On the "Build Settings" tab of your application target, add `-ObjC` to the "Other Linker Flags" build setting.

Imports
--------------
The OUX Plugin for Brightcove Player SDK for iOS can be imported into code a few different ways; `@import BrightcoveOUX;`, `#import <BrightcoveOUX/BrightcoveOUX.h>` or `#import <BrightcoveOUX/[specific class].h>`.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/brightcove/BrightcoveSpecs/tree/master/Brightcove-Player-OnceUX
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-oux/releases

Quick Start
===========
BrightcoveOUX is a plugin for [Brightcove Player SDK for iOS][bcovsdk] that provides support for Brightcove OnceUX server side ad stitching. Its use is relatively straightforward.

    [1] BCOVOUXAdComponentDisplayContainer *displayContainer = [[BCOVOUXAdComponentDisplayContainer alloc] initWithCompanionSlots:@[]];
        
        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];

    [2] id<BCOVPlaybackController> playbackController = [sdkManager createOUXPlaybackControllerWithViewStrategy:nil];

    [3] [playbackController addSessionConsumer:displayContainer];
    
    [4] [self.videoContainer addSubview:playbackController.view];
    
    [5] BCOVVideo *video = [BCOVVideo videoWithURL:[NSURL URLWithString:<url-to-once-ux-video>]];
    [6] [playbackController setVideos:@[ video ]];
        [playbackController play];

Let's break this code down into steps, to make it a bit simpler to digest:

1. First create a `BCOVOUXAdComponentDisplayContainer`. This object will help manage companion slots. Pass in the companion slots that you have, if any.
1. BrightcoveOUX adds some category methods to `BCOVPlaybackManager`. The first of these is `-createOUXPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. You will typically pass `nil` for the view strategy.
1. In order for the `BCOVOUXAdComponentDisplayContainer` to display ad information and populate companion ad views, it must be added as a session consumer.
1. Add the playback controller's view to the video container in your own view hierarchy.
1. Create a `BCOVVideo` using the URL to your OnceUX video.
1. Load the video into the playback controller.

If you have questions or need help, visit the support forum for Brightcove Native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Obtaining Ad playback Information
=======
BrightcoveOUX provides ad playback information via the `BCOVPlaybackControllerAdsDelegate`. For example, if you want to hide your controls during an ad, you could implement `-[BCOVPlaybackControllerAdsDelegate playbackController:playbackSession:didEnterAdSequence:]` to hide them.

For more information on how to use these delegate methods, please see [Brightcove Player SDK for iOS][bcovsdk].

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

Seeking
=======

The BrightcoveOUX plugin provides a seeking function that should be used when implementing controls. This seek function is exposed on the session through the `providerExtension` property. Here is how it is used:
    
    
    CMTime contentTimeToSeekTo = <calculation-from-scrub-bar>;
    [self.currentSession.providerExtension oux_seekToTime:contentTimeToSeekTo completionHandler:^(BOOL finished) {
    
        if (finished)
        {
            [self.currentSession.player play];
        }
    
    }];
    
The `completionHandler` will execute at the completion of a successful seek. It will not execute if a seek was already initiated by a previous call to `-[BCOVSessionProviderExtension oux_seekToTime:completionHandler:]` or if an ad is playing back. To test whether a see attempt can be made, check the `-[BCOVSessionProviderExtension oux_canSeek]` property. For more information on both of these methods, be sure to read the [headerdoc][oux_extensions].

[oux_extensions]: https://github.com/brightcove/brightcove-player-sdk-ios-oux/blob/master/ios/static/BrightcoveOUX.framework/Headers/BCOVOUXComponent.h

Seeking With Ads Disabled
=========================

The BrightcovePlayerSDK provides a BOOL property for disabling ads while seeking. The intended use by OnceUX is to allow an application to resume video playback after relaunching without requiring the end-user to view ads they've already seen.

It is recommended that ad-disabling logic be added to the `kBCOVPlaybackSessionLifecycleEventReady` handler of the `-playbackController:playbackSession:didReceiveLifecycleEvent:` method of your `BCOVPlaybackController` delegate.

	- (void)playbackController:(id<BCOVPlaybackController>)controller
	           playbackSession:(id<BCOVPlaybackSession>)session
	  didReceiveLifecycleEvent:(BCOVPlaybackSessionLifecycleEvent *)lifecycleEvent
	  {
	    if ([kBCOVPlaybackSessionLifecycleEventReady isEqualToString:lifecycleEvent.eventType])
	    {
	      // disable ads.
	      _playbackController.adsDisabled = YES;
	
	      // seek somewhere into the video content.
	      [session.providerExtension oux_seekToTime:resumeTime completionHandler:^(BOOL finished)
	      {
	        // re-enable ads.
	        _playbackController.adsDisabled = NO;
	
	        // open the shutter.
	        _playbackController.shutterFadeTime = 0.25;
	        _playbackController.shutter = NO;
	    }];
	  }

When calling `oux_seekTo:completion:` to resume playback at a particular time, the first frame of the video will be visible until the seek completes. For a cleaner presentation, temporarily cover the video view during seeking by setting the BOOL `shutter` property of BCOVPlabackController to `YES` before calling `-setVideos:`. When seeking is complete, dismiss the shutter by setting the `shutter` property to `NO`. The `shutterFadeTime` property defines the duration of the shutter fade animation.

	self.playbackController = [sdkManager createOUXPlaybackControllerWithViewStrategy:[sdkManager BCOVOUXdefaultControlsViewStrategy]];

	// resuming playback so activate the shutter before loading video.
	self.playbackController.shutterFadeTime = 0.0;
	self.playbackController.shutter = YES;

	NSArray *videos = @[[self videoWithURL: [NSURL URLWithString:onceUxUrl]]];
	[self.playbackController setVideos:videos];

Player UI Built-In Controls
===========================

The BrightcovePlayerSDK provides a built-in set of UI controls that can be used with the OnceUX plugin for both basic playback and ad controls. To use the controls, create a `BCOVPUIPlayerView`, and associate it with your OnceUX playback controller.

First, create a playerView property in your class.

     @property (nonatomic) BCOVPUIPlayerView *playerView;

Create the `BCOVPUIPlayerView` instance and save a reference to the object. Set its frame to match your container view, then add the player view to the container view in your view hierarchy. Note that `videoContainer` is your own view object in your app's layout.

     BCOVPUIBasicControlView *controlView = [BCOVPUIBasicControlView basicControlViewWithVODLayout];
     self.playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil options:nil controlsView:controlView];
     self.playerView.frame = self.videoContainer.bounds;
     self.playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;

     // Insert the playerView into your own video view.
     [self.videoContainer addSubview:self.playerView];

Now create the `BCOVPlaybackController`, assign it to your player view, and then start playing videos.

    // Initialize companion slots
    BCOVOUXAdComponentDisplayContainer *displayContainer = [[BCOVOUXAdComponentDisplayContainer alloc] initWithCompanionSlots:@[]];

    // Create the playback controller
    BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    id<BCOVPlaybackController> playbackController = [sdkManager createOUXPlaybackControllerWithViewStrategy:nil];

    // Listen for display/companion ad messages
    [playbackController addSessionConsumer:displayContainer];

	// Tell the player view this is the playback controller we're using
	self.playerView.playbackController = playbackController;
    
    // Create and play your video
    BCOVVideo *video = [BCOVVideo videoWithURL:[NSURL URLWithString:<url-to-once-ux-video>]];
    [playbackController setVideos:@[ video ]];
    [playbackController play];

See the README in the BrightcovePlayerSDK for more details about how to use and customize the PlayerUI controls.

Known Issues
==========================

* You cannot use BrightcoveOUX with any other Brightcove plugins except for the BrightcoveFairPlay plugin.

* The plugin currently does not support playing back OnceUX content and non OnceUX content in the same playback controller. If you need to play both, you will need to create a separate playback controller for this content.

* When playing OnceUX content, you may see a message in the log that states "No source found with deliveryMethod of HLS or MP4, falling back to the first source.". This message can be ignored and will be addressed in a future update.

* If the request for the OnceUX VMAP document fails to load, in addition to receiving an error event, you may see a message in the log that states "Cannot -forwardInvocation: to nonexistent inner playback session.". This message can be ignored and will be addressed in a future update.
