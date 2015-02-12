//
// BCOVOUXSessionProvider.h
// BCOVOUX
//
// Copyright (c) 2015 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import "BCOVPlayerSDK.h"


/**
 * Session provider implementation that delivers playback sessions with support
 * for Brightcove OnceUX.
 *
 * Instances of this class should not be created directly by clients of the
 * Brightcove Player SDK for iOS; instead use the `-[BCOVPlayerSDKManager createOUXSessionProviderWithOptions:]`
 * factory method (which is added as a category method).
 */
@interface BCOVOUXSessionProvider : NSObject <BCOVPlaybackSessionProvider>

@end


/**
 * Optional configuration for BCOVOUX session providers.
 */
@interface BCOVOUXSessionProviderOptions : NSObject

@end
