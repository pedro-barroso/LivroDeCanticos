//
//  LSLocaytaSearchBalancer.h
//  LocaytaSearch
//
//  Created by Nick Murdoch on 12/07/2012.
//  Copyright (c) 2012 Locayta Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LSQuery;
@class LSWeightingSystem;

/**
 * \page balance_factors Using Locayta Balance Factor technology to change the order of results
 *
 * While simple sorting of results by one of their field values is handled
 * by LSLocaytaSearchRequest instances, classes called \a balancers can be used to provide
 * more sophisticated ordering of results, either by dynamically calculating
 * distance from a central point in the case of LSLocaytaSearchDistanceBalancer,
 * or by mixing the ordering of a simple sort with the standard relevance to
 * give better results in the case of LSLocaytaSearchStoredValBalancer.
 *
 * Balancing search results involves combining the usual weight (relevance) of
 * a result with another measurement. This allows results to be balanced, 
 * biased, or boosted based on a metric separate from the main weighting
 * algorithm. Each balancer returns one value per document, which is mixed with
 * the text relevance of that document to determine the final order of results.
 *
 * The caller also gives each balancer a weighting multiplier that is used to
 * determine how much the balancer's returned values affect the order of
 * results. This is called the Balance Factor.
 *
 * Instances of LSLocaytaSearchBalancer subclasses are used by setting the
 * balancers property of LSLocaytaSearchQuery instances to an array containing
 * all the balancers required. It is common to use just one balancer
 * at a time since using multiple balancers can become difficult to predict,
 * but there is no technical reason why several balancers can't be used together.
 *
 * Locayta Search Mobile currently comes with two types of balancers built-in.
 * See the following pages for more information:
 *
 *    - \subpage boosting-results
 *    - \subpage geolocation
 *
 */

/** \brief Base class for \ref balance_factors "search balancers".
 *
 * This class should not be used directly; use one of the provided subclasses.
 */
@interface LSLocaytaSearchBalancer : NSObject {
    double factor;
    LSWeightingSystem * weightingSystem;
}

@property (nonatomic, assign) double factor;
@property (nonatomic, readonly) LSWeightingSystem * weightingSystem;

- (LSQuery*)leafQuery;

@end
