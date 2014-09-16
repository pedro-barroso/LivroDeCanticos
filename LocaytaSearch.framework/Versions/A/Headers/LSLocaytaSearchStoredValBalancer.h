//
//  LSLocaytaSearchStoredValBalancer.h
//  LocaytaSearch
//
//  Created by Nick Murdoch on 23/07/2012.
//  Copyright (c) 2012 Locayta Limited. All rights reserved.
//

#import "LSLocaytaSearchBalancer.h"

/**
 \page boosting-results Balancing and boosting results using a field value
 
 [Note: to simply sort results by the value in a field (eg price), use LSLocaytaSearchRequest#sortOrder]
 
 Locayta Search Mobile provides functionality to mix the standard text
 relevance score of results with values stored in each document using its
 \ref balance_factors "balance factor" technology. This allows you
 to "balance" the order of results from a search ordered by text relevance with
 the order of results from a search ordered by a simple field sort.
 
 Balancing could be to provide a boost to desirable documents so they appear
 higher up in the search listings than they otherwise would, without
 the disadvantage of leaving all results in an arbitrary order
 afterwards. The amount the documents are boosted depends on the <em>balance
 factor</em> of the desirability field.
 
 For example, if you have a collection of research papers, you may want to
 prioritise papers that have more citations, but you would still want a
 document with few citations to appear reasonably high in the results if it
 matched the user's query well.
 
 The LSLocaytaSearchStoredValBalancer class provides this functionality. It
 it initialised using the slot number used to store the numeric data in the
 \ref schema and requires the data to be contained within a known range (for
 example, percentage values are in the range 0 - 100).
 
 \code
 LSLocaytaSearchQuery *searchQuery = [LSLocaytaSearchQuery queryWithQueryString:searchQuery];
 searchQuery.balanceFactor = textBalanceFactor;
 
 LSLocaytaSearchStoredValBalancer *balancer = [LSLocaytaSearchStoredValBalancer balancerWithFactor:balanceFactor slot:balanceSlot rangeMin:0 rangeMax:100];
 NSArray *balancers = [NSArray arrayWithObject:balancer];
 searchQuery.balancers = balancers;
 
 [searchRequest searchWithQuery:searchQuery];
 \endcode
 
 The weights of the search results are adjusted in accordance with the values
 in the balancers' slot and the relative factors of the balancers.
 
 For example, suppose we indexed the following product data with a \ref schema
 that set index=YES for title and numericslot=1 for score:
 
 \verbatim
 id=1
 title=Apple iPhone
 score=0
 
 id=2
 title=Apple iPad
 score=50
 
 id=3
 title=Apple iPod Touch
 score=100
 \endverbatim
 
 A regular search for "apple" would return the following weights:
 
 - Apple iPhone: 1.00
 - Apple iPad: 1.00
 - Apple iPod Touch: 0.90 
 
 If in the code above we set textBalanceFactor to 0.0 and balanceFactor to 1.0,
 this would give the balancer full control over the order of results (and they
 would be ordered identically to setting the sortOrder of LSLocaytaSearchRequest
 to @"-1"). The weights from the balancer would appear in the results as such:
 
 - Apple iPod Touch: 1.00
 - Apple iPad: 0.50
 - Apple iPhone: 0.00
 
 Now, if we set textBalanceFactor to 0.9 and balanceFactor to 0.1, the results
 end up as a mix of the two examples above:
 
 - Apple iPad: 1.00
 - Apple iPod Touch: 0.96
 - Apple iPhone: 0.95
 
 Note that the weights are rescaled so that the top result always has a weight
 of 1.0.
 */

/** \brief A class used for reordering results by the value in a numeric field
 *
 * Note: to perform a simple sort of results, this class is not needed. See
 * LSLocaytaSearchRequest::sortOrder instead.
 *
 * This class provides a \ref balance_factors "balancer" that weights documents
 * using a value stored during indexing using the 'numericslot' \ref schema
 * option.
 *
 * To use this balancer effectively, you need to know the range of values
 * that are expected to be found in this slot. This is straightforward for (eg)
 * percentage values, but for other metrics you may need to apply a normalisation
 * calculation before indexing.
 *
 * \see \ref boosting-results
 */
@interface LSLocaytaSearchStoredValBalancer : LSLocaytaSearchBalancer {
    
}

/** \brief	Returns an autoreleased instance of LSLocaytaSearchStoredValBalancer
 *
 * This is a convenience function for [[[LSLocaytaSearchStoredValBalancer alloc] initWithFactor:...] autorelease];
 */
+ (id) balancerWithFactor:(double)balanceFactor slot:(int)slot rangeMin:(double)rangeMin rangeMax:(double)rangeMax;

/**
 * \brief	Returns a new instance of LSLocaytaSearchStoredValBalancer for the given slot and range.
 *
 * @param slot is the slot number that was used when indexing to store the geolocation data.
 *
 * @param rangeMin is a floating point number that should be set to the lowest
 *   expected value for the field.
 *
 * @param rangeMax is a floating point number that should be set to the highest
 *   expected value for the field.
 *
 * The range parameters are required to allow Locayta Search to balance the
 * values with the text relevance of a result correctly.
 */
- (id) initWithFactor:(double)balanceFactor slot:(int)slot rangeMin:(double)rangeMin rangeMax:(double)rangeMax;

@end
