//
// BCOVOUXComponent.h
// BrightcoveOUX
//
// Copyright (c) 2016 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <CoreMedia/CoreMedia.h>

#import <BrightcovePlayerSDK/BrightcovePlayerSDK.h>

@class BCOVOUXSessionProviderOptions;


NS_ASSUME_NONNULL_BEGIN

/**
 * Category methods added to BCOVPlayerSDKManager to support BCOVOUX.
 */
@interface BCOVPlayerSDKManager (BCOVOUXAdditions)

/**
 * Creates and returns a new playback controller with the specified view
 * strategy. The returned playback controller will be configured with a
 * BCOVOUX session provider.
 *
 * @param strategy A view strategy that determines the view for the returned
 * playback controller.
 * @return A new playback controller with the specified parameters.
 */
- (id<BCOVPlaybackController>)createOUXPlaybackControllerWithViewStrategy:(nullable BCOVPlaybackControllerViewStrategy)strategy;

/**
 * Creates and returns a new BCOVOUX session provider with the specified
 * parameters.
 *
 * @param provider Optional upstream session provider.
 * @return A new BCOVOUXSessionProvider with the specified parameters.
 */
- (id<BCOVPlaybackSessionProvider>)createOUXSessionProviderWithUpstreamSessionProvider:(nullable id<BCOVPlaybackSessionProvider>)provider;


/**
 * Returns a view strategy that wraps the video view it is given with the
 * default playback controls.
 *
 * This view strategy is intended to provide a "stock" set of controls to aide
 * development, testing, and Brightcove code samples.
 *
 * @return A view strategy block that wraps the video view with stock controls.
 */
- (BCOVPlaybackControllerViewStrategy)BCOVOUXdefaultControlsViewStrategy;

@end


/**
 * OUX specific methods for the plugin context.
 */
@interface BCOVSessionProviderExtension (BCOVOUXAdditions)

/**
 * The value of this property indicates whether the receiver will ignore `oux_seekToTime:completionHandler:`
 * or not. The value is NO when either an ad is in progress or the receiver 
 * is still processing a previous messaging of `oux_seekToTime:completionHandler:`;
 * otherwise, the value of this property is YES. See also `oux_seekToTime:completionHandler:`.
 */
@property (nonatomic, readonly) BOOL oux_canSeek;

/**
 * This method implements the default seek behaviour for the BCOVOUX plugin.
 * This method must be called on the main thread. The receiver will ignore this
 * meassage when either an ad is in progress or a previous call to `oux_seekToTime:completionHandler:` 
 * is still being processed. See also `oux_canSeek`.
 *
 * The rules are as follows:
 *
 * - If seeking to end of the logical content time, the post rolls will play.
 * - If seeking over an ad sequence, the ad will play, and the playhead will resume
 * where the seek had attempted to seek to.
 * - If seeking over multiple ad sequences, only the last ad sequence will play.
 * - If seeking backwards, no ads will play.
 * - If seeking over ads that have already been played, they will play again.
 *
 * @param time The logical time to seek to
 * @param completionHandler The block to execute when the seek is performed
 */
- (void)oux_seekToTime:(CMTime)time completionHandler:(void (^)(BOOL finished))completionHandler;

@end

NS_ASSUME_NONNULL_END
