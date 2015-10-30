# BCOVOUX Plugin for Brightcove Player SDK for iOS, version 1.0.3.118

Requirements
============
This plugin supports iOS 7.0+ and Xcode 6.0+.

Installation
============
You can use [Cocoapods][cocoapods] to add the OUX Plugin for Brightcove Player SDK to your project.  You can find the latest `Brightcove-Player-SDK-OUX` podspec [here][podspecs].

To add the OUX Plugin for Brightcove Player SDK to your project manually:

1. Install the latest version of the [Brightcove Player SDK][bcovsdk].
1. Download the latest zip'ed release of the plugin from our [release page][release].
1. Add the contents of Library and Headers to the project.
1. On the "Build Phases" tab of your application target, add the following to the "Link
    Binary With Libraries" phase:
    * `libBCOVOUX.a`
    * `libxml2.2.dylib`
    * `WebKit.framework`; set status as `optional`.
1. On the "Build Settings" tab of your application target:
    * Ensure that BCOVOUX headers are in your application's "Header Search Path".
    * Ensure that `-ObjC` has been added to the "Other Linker Flags" build setting.

[cocoapods]: http://cocoapods.org
[podspecs]: https://github.com/CocoaPods/Specs/tree/master/Specs/Brightcove-Player-SDK-OUX
[release]: https://github.com/brightcove/brightcove-player-sdk-ios-oux/releases

Quick Start
===========
BCOVOUX is a plugin for [Brightcove Player SDK for iOS][bcovsdk] that provides support for Brightcove OnceUX server side ad stitching. Its use is relatively straightforward.

    [1] BCOVOUXAdComponentDisplayContainer *displayContainer = [[BCOVOUXAdComponentDisplayContainer alloc] initWithAdComponentContainer:self.videoContainer companionSlots:nil];
    
        BCOVPlayerSDKManager *manager = [BCOVPlayerSDKManager sharedManager];
    [2] id<BCOVPlaybackController> controller = [manager createOUXPlaybackControllerWithViewStrategy:[manager BCOVOUXdefaultControlsViewStrategy]];
        controller.delegate = self;
    [3] [controller addSessionConsumer:displayContainer];
    
    [4] [self.videoContainer addSubview:controller.view];
    
    [5] BCOVVideo *video = [BCOVVideo videoWithURL:[NSURL URLWithString:<url-to-once-ux-video>]];
    [6] [controller setVideos:@[ video ]];
        [controller play];

Let's break this code down into steps, to make it a bit simpler to digest:

1. First you will want to create an BCOVOUXAdComponentDisplayContainer. This object will provide the ad UI and help manage any companion slots. Pass in the view you want the ad UI to show up in and any companion slots that you have, if any.
1. BCOVOUX adds some category methods to BCOVPlaybackManager. The first of these is `-createOUXPlaybackControllerWithViewStrategy:`. Use this method to create your playback controller.
1. In order for the BCOVOUXAdComponentDisplayContainer to display ad information and populate companion ad views, it must be added as a session consumer.
1. Add the playback controller's view to your video container. This will probably be the same view you used in step 1.
1. Create a BCOVVideo using the URL to your OnceUX VMAP document.
1. Load the video into the playback controller.

If you have questions or need help, we have a support forum for Brightcove's native Player SDKs at [https://groups.google.com/forum/#!forum/brightcove-native-player-sdks][forum] .

[forum]: https://groups.google.com/forum/#!forum/brightcove-native-player-sdks

Obtaining Ad playback Information
=======
BCOVOUX provides ad playback information via the `BCOVPlaybackControllerAdsDelegate`. For example, if you want to hide your controls during an ad, you could implement `-[BCOVPlaybackControllerAdsDelegate playbackController:playbackSession:didEnterAdSequence:]` to hide them.

For more information on how to use these delegate methods, please see [Brightcove Player SDK for iOS][bcovsdk].

[bcovsdk]: https://github.com/brightcove/brightcove-player-sdk-ios

Seeking
=======

The BCOVOUX plugin provides a seeking function that should be used when implementing controls. This seek function is exposed on the session through the `providerExtension` property. Here is how it is used:
    
    
    CMTime contentTimeToSeekTo = <calculation-from-scrub-bar>;
    [self.currentSession.providerExtension oux_seekToTime:contentTimeToSeekTo completionHandler:^(BOOL finished) {
    
        if (finished)
        {
            [self.currentSession.player play];
        }
    
    }];
    
The `completionHandler` will execute at the completion of a successful seek. It will not execute if a seek was already initiated by a previous call to `-[BCOVSessionProviderExtension oux_seekToTime:completionHandler:]` or if an ad is playing back. To test whether a see attempt can be made, check the `-[BCOVSessionProviderExtension oux_canSeek]` property. For more information on both of these methods, be sure to read their [headerdoc][oux_extensions].

[oux_extensions]: https://github.com/brightcove/brightcove-player-sdk-ios-oux/blob/master/Headers/BCOVOUXComponent.h

Known Issues
==========================

* You can not use BCOVOUX with any other BCOV plugins.

* The plugin currently does not support playing back OnceUX content and non OnceUX content in the same playback controller. If you need to play both, you will need to create a separate playback controller for this content.

* When playing OnceUX content, you may see a message in the log that states "No source found with deliveryMethod of HLS or MP4, falling back to the first source.". This message can be ignored and will be addressed in a future update.

* If the request for the OnceUX VMAP document fails to load, in addition to receiving an error event, you may see a message in the log that states "Cannot -forwardInvocation: to nonexistent inner playback session.". This message can be ignored and will be addressed in a future update.
