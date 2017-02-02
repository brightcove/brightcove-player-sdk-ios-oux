//
// BCOVOUXConstants.h
// BrightcoveOUX
//
// Copyright (c) 2017 Brightcove, Inc. All rights reserved.
// License: https://accounts.brightcove.com/en/terms-and-conditions
//

#import <Foundation/Foundation.h>

/**
 * NSError domain for errors generated by BCOVOUX.
 */
extern NSString * const kBCOVOUXErrorDomain;

/**
 * Error code used to indicate that an error occurred while loading a timeline.
 */
extern const NSInteger kBCOVOUXErrorCodeTimelineLoadError;

/**
 * BCOVPlaybackSessionLifecycleEvent.eventType for lifecycle events that
 * communicate errors specific to BCOVOUX.
 */
extern NSString * const kBCOVOUXLifecycleErrorEvent;

/**
 * BCOVPlaybackSessionLifecycleEvent.properties key for the underlying NSError
 * when the eventType is `kBCOVOUXLifecycleErrorEvent`.
 */
extern NSString * const kBCOVOUXLifecycleEventPropertiesKeyError;
