//
// BCOVOUXConstants.h
// BrightcoveOUX
//
// Copyright (c) 2019 Brightcove, Inc. All rights reserved.
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

/**
 * XML elements are sometimes represented as NSDictionary objects. The NSDictionary
 * contains the XML element start tag (NSString), attributes (NSDictionary) and
 * content. When the element is a leaf node, the content is the element text
 * (NSString). When the element contains one or more child elements, the content
 * is an an array (NSArray) of XML elements (NSDictionary objects).
 *
 * Using the following XML snippet - a hypothetical VAST ad extension - as an
 * example:
 *
 * <Extensions>
 *   <Extension type="Freelance">
 *     <parameters>
 *       <parameter name="mope"><![CDATA[375613;g669038;17566919]]</parameter>
 *       <parameter name="lmno_parameters"><![CDATA[8968;OldMacDonalds]]</parameter>
 *     </parameters>
 *   </Extension>
 * </Extensions>
 *
 * The following structure is generated where ( and ) indicate an NSArray and
 * { and } indicate an NSDictionary, as would be seen when NSlog'ing the
 * description of each class.
 *
 * (
 *   {
 *     "tag" = Extension;
 *     "attributes" = { type = "Freelance" }
 *     "content" =
 *     (
 *       {
 *         "tag" = parameters;
 *         "attributes" = {};
 *         "content" =
 *         (
 *           {
 *             "tag" = parameter;
 *             "attributes" = { name = mope; };
 *             "content" = "375613;g669038;17566919";
 *           },
 *           {
 *             "tag" = parameter;
 *             "attributes" = { name = "lmno_parameters"; };
 *             "content" = "8968;OldMacDonalds";
 *           }
 *         );
 *       }
 *     );
 *   }
 * )
 *
 * https://www.w3schools.com/xml/xml_elements.asp
 *
 */
extern NSString * const kBCOVXMLElementTagKey;
extern NSString * const kBCOVXMLElementAttributesKey;
extern NSString * const kBCOVXMLElementContentKey;

/**
 * When a VAST ad contains, e.g., VAST ad Extensions (plural), the list of Extension
 * (singular) XML elements is stored in the properties NSDictionary of the
 * BCOVAd object passed to the BCOVPlaybackControllerAdsDelegate methods. The same
 * is true for VAST ad CreativeExtensions. As an example:
 *
 * - (void)playbackController:(id<BCOVPlaybackController>)controller
 *            playbackSession:(id<BCOVPlaybackSession>)session
 *                 didEnterAd:(BCOVAd *)ad
 * {
 *    NSArray *vastAdCreativeExtensions = ad.properties[kBCOVOUXVASTAdCreativeExtensionsKey];
 *    NSArray *vastAdExtensions = ad.properties[kBCOVOUXVASTAdExtensionsKey];
 *
 * ad.properties[kBCOVOUXVASTAdCreativeExtensionsKey] will be nil if the VAST ad does not
 * contain CreativeExtensions. ad.properties[kBCOVOUXVASTAdExtensionsKey] will be nil
 * if the VAST ad does not contain ad Extensions.
 */
extern NSString * const kBCOVOUXVASTAdCreativeExtensionsKey;
extern NSString * const kBCOVOUXVASTAdExtensionsKey;

/*
 * Notification that is sent out when we receive a VMAP document response
 */
extern NSString * const kBCOVOUXVMAPResponseReceivedNotification;
/*
 * The notification's userInfo dictionary key for the raw VMAP data
 */
extern NSString * const kBCOVOUXVMAPResponseReceivedNotificationDataUserInfoKey;
