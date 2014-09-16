//
//  LSLocaytaSearchDistanceBalancer.h
//  LocaytaSearch
//
//  Created by Nick Murdoch on 12/07/2012.
//  Copyright (c) 2012 Locayta Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LSLocaytaSearchBalancer.h"

/**
 \page geolocation Geolocation Searching
 
 Locayta Search Mobile provides functionality to order results by their
 distance from a known location using its \ref balance_factors "balance factor"
 technology. 

 Indexing documents so that they can be used for geolocation is
 straightforward. The only extra information you need to give to the index
 are the co-ordinates of each document. These should be in the format
 \code @"{latitude}:{longitude}" \endcode where {latitude} and {longitude} are
 floating point numbers representing a number of degrees. The field these are
 stored in must be given a unique stringslot (see \ref schema).

 For example:
 
 \code
 LSLocaytaSearchIndexableRecord *indexableRecord = [[LSLocaytaSearchIndexableRecord alloc] initWithSchema:searchSchema];
 [indexableRecord addValue:@"1" forField:@"id" error:&error];
 [indexableRecord addValue:@"London Bridge" forField:@"title" error:&error];
 [indexableRecord addValue:@"51.508056:-0.087778" forField:"location" error:&error];
 \endcode
 
 (See \subpage search_updates for a full indexing example.)
 
 When searching, add an instance of the LSLocaytaSearchDistanceBalancer class
 to the balancers property of LSLocaytaSearchQuery object:
 
 \code
 LSLocaytaSearchQuery *searchQuery = [LSLocaytaSearchQuery queryWithQueryString:@"London"];
 LSLocaytaSearchDistanceBalancer *distanceBalancer = [LSLocaytaSearchDistanceBalancer balancerWithFactor:1.0 slot:locationFieldSlot latitude:current.latitude longitude:current.longitude];
 NSArray *balancers = [NSArray arrayWithObject:distanceBalancer];
 searchQuery.balancers = balancers;
 searchQuery.balanceFactor = 0;
 [searchRequest searchWithQuery:searchQuery topDocIndex:0 docsPerPage:10];
 \endcode
 
 This will return all results that match the query string "London", ordered by
 their distance from the location given to the LSLocaytaSearchDistanceBalancer.
 
 For this balancer, the only predictable balance factors are 1.0 for
 LSLocaytaSearchDistanceBalancer instances and 0.0 for LSLocaytaSearchQuery
 instances, as shown above.
 
 \section displaying-distances Displaying distances in results
 
 The distance balancer also contains two methods for calculating the distance
 to the balancer's centre point:
 
 - LSLocaytaSearchDistanceBalancer#distanceFromLatLong:
 - LSLocaytaSearchDistanceBalancer#distanceFromLatitude:longitude:
 
 These return the distances in metres. For example:
 
 \code
 for (NSDictionary *result in searchResults.results) {
     NSDictionary *fields = [result valueForKey:@"fields"];
     NSString *location = [[fields valueForKey:@"location"] objectAtIndex:0];
     double distance = [distanceBalancer distanceFromLatLong:location];
     NSLog(@"distance: %fm", distance);
 }
 \endcode
 
 Please note that Locayta Search does not take altitude into account and assumes
 the Earth is a perfect sphere, so distances are approximate. That said, they
 are suitable for most purposes where as-the-crow-flies distance is wanted.
 */


/**
 * \brief	A class used for reordering results by their distance from a known point on Earth.
 *
 * This provides a \ref balance_factors "balancer" that weights documents
 * using geolocation provided by the Haversine distance formula.
 * Results nearer to the balancer's given centre are weighted higher.
 *
 * For this balancer, the only predictable balance factors are 1.0 for
 * LSLocaytaSearchDistanceBalancer instances and 0.0 for LSLocaytaSearchQuery
 * instances. This will order results in order of their distance from the
 * given \a centre point.
 *
 * Example:
 * \code
 * // weight results by distance from London, UK:
 * LSLocaytaSearchQuery *searchQuery = [LSLocaytaSearchQuery queryWithQueryString:@"bridge"];
 * LSLocaytaSearchDistanceBalancer *distanceBalancer = [LSLocaytaSearchDistanceBalancer balancerWithFactor:1.0 slot:1 latitude:coord2d.latitude longitude:coord2d.longitude];
 * NSArray *balancers = [NSArray arrayWithObject:distanceBalancer];
 * searchQuery.balancers = balancers;
 * searchQuery.balanceFactor = 0;
 * // perform the search...
 * \endcode
 *
 * \see \ref geolocation
 */ 
@interface LSLocaytaSearchDistanceBalancer : LSLocaytaSearchBalancer {

}

/**
 * \brief	Returns an autoreleased instance of LSLocaytaSearchDistanceBalancer
 *
 * This is a convenience method for [[[LSLocaytaSearchDistanceBalancer alloc] initWithFactor:...] autorelease];
 */
+ (id) balancerWithFactor:(double)balanceFactor slot:(int)slot latLong:(NSString *)latLong;

/**
 * \brief	Returns an autoreleased instance of LSLocaytaSearchDistanceBalancer
 *
 * This is a convenience method for [[[LSLocaytaSearchDistanceBalancer alloc] initWithFactor:...] autorelease];
 */
+ (id) balancerWithFactor:(double)balanceFactor slot:(int)slot latitude:(double)latitude longitude:(double)longitude;

/**
 * \brief	Returns a new instance of LSLocaytaSearchDistanceBalancer for the given latitude and longitude.
 *
 * @param latLong an NSString containing the latitude and longitude in the format
 * "%f:%f". This will be used as the centre point of the search.
 *
 * @param slot the slot number that was used when indexing to store the geolocation data.
 */
- (id)initWithFactor:(double)balanceFactor slot:(int)slot latLong:(NSString *)latLong;

/**
 * \brief	Returns a new instance of LSLocaytaSearchDistanceBalancer for the given latitude and longitude.
 *
 * @param latitude a double representing the centre point's latitude in degrees
 *             (North is positive, South is negative). It should be -90<latitude<90.
 *
 * @param longitude a double represending the centre point's longitude in degrees
 *             (East is positive, West is negative). It should be -180<longitude<180.
 *
 * @param slot the slot number that was used when indexing to store the geolocation data.
 */
- (id)initWithFactor:(double)balanceFactor slot:(int)slot latitude:(double)latitude longitude:(double)longitude;

/**
 * \brief	Calculate the distance in metres from the given coordinates to this balancer's stored coordinates.
 * 
 * @param latLong a string in the format @"latitude:longitude" where
 * \a latitude is a floating point number representing the latitude in degrees, and
 * \a longitude is a floating point number representing the longitude in degrees.
 */
- (double) distanceFromLatLong:(NSString*)latLong;

/**
 * \brief	Calculate the distance in metres from the given coordinates to this balancer's stored coordinates.
 *
 * @param latitude a floating point number representing the latitude in degrees.
 *
 * @param longitude a floating point number representing the longitude in degrees.
 */
- (double) distanceFromLatitude:(double)latitude longitude:(double)longitude;

@end
