# Brightcove OnceUX Plugin for Brightcove Player SDK for iOS, version 6.4.3.616

Important Notice
================

The OnceUX Plugin has been replaced by the SSAI Plugin for Brightcove Player SDK for iOS and all OnceUX features are available in SSAI. Refer to the "Migrating OnceUX to SSAI" section of this README for details on upgrading your application. The SSAI plugin can be found [here](https://github.com/brightcove/brightcove-player-sdk-ios-ssai).

Supported Platforms
===================
iOS 10.0 and above.

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

When updating your installation, it's a good idea to refresh the local copy of your BrightcoveSpecs repository so that you have the latest podspecs locally, just like you would update your CococaPods master repository.

Typically if you use `pod update` in Terminal this will happen automatically, or alternatively you can update explicitly with `pod repo update brightcove`. (Your BrightcoveSpecs repository may have a different name if you explicitly added it to your list of podspecs repos.)

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

To summarize:

1. First create a `BCOVOUXAdComponentDisplayContainer`. This object will help manage companion slots. Pass in the companion slots that you have, if any.
1. BrightcoveOUX adds some category methods to `BCOVPlaybackManager`. The first of these is `-createOUXPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller. You will typically pass `nil` for the view strategy.
1. In order for the `BCOVOUXAdComponentDisplayContainer` to display ad information and populate companion ad views, it must be added as a session consumer.
1. Add the playback controller's view to the video container in your own view hierarchy.
1. Create a `BCOVVideo` using the URL to your OnceUX video.
1. Load the video into the playback controller.

If you have questions or need help, visit the support forum for Brightcove Native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Migrating OnceUX to SSAI
=======

The BrightcoveSSAI plugin framework is taking the place of BrightcoveOUX. BrightcoveSSAI supports all the current features of BrightcoveOUX, however future updates will only be added to BrightcoveSSAI. Follow these instructions to migrate your OnceUX application to Brightcove SSAI.

1) If you install Brightcove plugins using CocoaPods, update your Podfile by changing `Brightcove-Player-OnceUX` to `Brightcove-Player-SSAI`, for example this:
```
target 'MyVideoPlayer' do
	pod 'Brightcove-Player-OnceUX/dynamic'
end
```
becomes this:
```
target 'MyVideoPlayer' do
	pod 'Brightcove-Player-SSAI/dynamic'
end
```
If you use static frameworks, leave off `/dynamic` like this: `pod 'Brightcove-Player-SSAI'`. Run `'pod update'` when ready.

If you install the Brightcove plugins manually, delete the Brightcove-Player-OnceUX framework from your Xcode project and follow the steps above to manually add the Brightcove-Player-SSAI framework.

2) In your source code, for all @import / #import statements, data types, method names, properties, constants and protocols which refer to the BrightcoveOUX framework, change every occurrence of "OUX" to "SSAI". A partial list is here:
 
    "@import BrightcoveOUX;" is now "@import BrightcoveSSAI;"
    "createOUXSessionProviderWithUpstreamSessionProvider" is now "createSSAISessionProviderWithUpstreamSessionProvider"
    "createOUXPlaybackControllerWithViewStrategy" is now "createSSAIPlaybackControllerWithViewStrategy"
    "oux_seekToTime" is now "ssai_seekToTime"
    "BCOVOUXAdComponentDisplayContainer" is now "BCOVSSAIAdComponentDisplayContainer"
    "BCOVOUXCompanionSlot" is now "BCOVSSAICompanionSlot"

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
    
The `completionHandler` will execute at the completion of a successful seek. It will not execute if a seek was already initiated by a previous call to `-[BCOVSessionProviderExtension oux_seekToTime:completionHandler:]` or if an ad is playing back. To test whether a seek attempt can be made, check the `-[BCOVSessionProviderExtension oux_canSeek]` property. For more information on both of these methods, be sure to read the [headerdoc][oux_extensions].

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

	NSArray *videos = @[[BCOVVideo videoWithURL: [NSURL URLWithString:onceUxUrl]]];
	[self.playbackController setVideos:videos];

Player UI Built-In Controls
===========================

The BrightcovePlayerSDK provides a built-in set of UI controls that can be used with the OnceUX plugin for both basic playback and ad controls. To use the controls, create a `BCOVPUIPlayerView`, and associate it with your OnceUX playback controller.

First, create a playerView property in your class.

     @property (nonatomic) BCOVPUIPlayerView *playerView;

Create the `BCOVPUIPlayerView` instance and save a reference to the object.

     BCOVPUIBasicControlView *controlView = [BCOVPUIBasicControlView basicControlViewWithVODLayout];
     self.playerView = [[BCOVPUIPlayerView alloc] initWithPlaybackController:nil options:nil controlsView:controlView];
     // Insert the playerView into your own video view.
     [self.videoContainer addSubview:self.playerView];

You'll need to set up the layout for the player view, you can do this with Auto Layout or the older Springs & Struts method. 

**Springs & Struts**

Set its frame to match your container view, then add the player view to the container view in your view hierarchy. Note that `videoContainer` is your own view object in your app's layout.

     self.playerView.frame = self.videoContainer.bounds;
     self.playerView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;

**Auto Layout**

    self.playerView.translatesAutoresizingMaskIntoConstraints = NO;
    [NSLayoutConstraint activateConstraints:@[
                                              [self.playerView.topAnchor constraintEqualToAnchor:self.videoContainer.topAnchor],
                                              [self.playerView.rightAnchor constraintEqualToAnchor:self.videoContainer.rightAnchor],
                                              [self.playerView.leftAnchor constraintEqualToAnchor:self.videoContainer.leftAnchor],
                                              [self.playerView.bottomAnchor constraintEqualToAnchor:self.videoContainer.bottomAnchor],
                                              ]];

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

Access to VMAP Response Data
==========================
Should you want access to the VMAP response data you can subscribe to the `kBCOVOUXVMAPResponseReceivedNotification` notification. Once received, the notification's userInfo dictionary will contain the VMAP response as NSData. You can use the `kBCOVOUXVMAPResponseReceivedNotificationDataUserInfoKey` constant to access it from userInfo. Since you may have multiple playback controllers, and thus multiple VMAP responses, you can check the notification's object, `id playbackController = notification.object` to verify which video the VMAP data is for. Additionally, when you subscribe to the notification you can set a playback controller as the object so that only VMAP data notifications regarding that playback controller will be received. For example:

```
[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(vmapResponseReceived:) name:kBCOVOUXVMAPResponseReceivedNotification object:self.playbackController];
```

Known Issues
==========================

* You cannot use BrightcoveOUX with any other Brightcove plugins except for the BrightcoveFairPlay plugin.

* The plugin currently does not support playing back OnceUX content and non OnceUX content in the same playback controller. If you need to play both, you will need to create a separate playback controller for this content.

* When playing OnceUX content, you may see a message in the log that states "No source found with deliveryMethod of HLS or MP4, falling back to the first source.". This message can be ignored and will be addressed in a future update.

* If the request for the OnceUX VMAP document fails to load, in addition to receiving an error event, you may see a message in the log that states "Cannot -forwardInvocation: to nonexistent inner playback session.". This message can be ignored and will be addressed in a future update.
