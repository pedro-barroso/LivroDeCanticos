//
//  LocaytaSearchQuery.h
//  LocaytaSearch
//
//  Created by Chris Miles on 19/04/10.
//  Copyright 2010-2011 Locayta Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LSLocaytaSearchError.h"

/**
 * \brief	The default operator to use when constructing a search query.
 *
 * Default is to find documents matching any search term in the query string
 * (e.g. "term1 OR term2 OR term3").
 */
typedef enum {
    LSLocaytaSearchQueryOperatorOr = 0,		// Find results containing any search terms
    LSLocaytaSearchQueryOperatorAnd,		// Find results containing all search terms
    LSLocaytaSearchQueryOperatorPhrase		// Find results containing all search terms in sequential order
} LSLocaytaSearchQueryOperator;


@class LSDatabaseReader;
@class LSQuery;


/**
 * \brief	A class representing a text search query with optional filters.
 *
 * Parses a query string into searchable terms, optionally applying any boolean
 * filters.  Instances of LSLocaytaSearchQuery are passed to LSLocaytaSearchRequest
 * to perform the actual search request.
 */ 
@interface LSLocaytaSearchQuery : NSObject {
    
    LSLocaytaSearchQueryOperator defaultOperator;
    NSDictionary *filters;
    NSDictionary *numericFilters;
    NSString *queryString;
    double balanceFactor;
    double threshold;
    NSArray *balancers;
    
@private
    LSQuery *_query;
    NSString *_stemmingLanguage;
    LSDatabaseReader *_synonymsDatabaseReader;
    LSQuery *_text_query;
    NSDictionary *_unstemmedTerms;
}

/**
 * \brief	The default operator to use when constructing a search query.
 *
 * Choices available are:
 *
 * \code
 * searchQuery.defaultOperator = LSLocaytaSearchQueryOperatorOr;
 * \endcode
 * Match documents containing any of the search terms (default).
 *
 * \code
 * searchQuery.defaultOperator = LSLocaytaSearchQueryOperatorAnd;
 * \endcode
 * Match only documents that contain all of the search terms.
 *
 * \code
 * searchQuery.defaultOperator = LSLocaytaSearchQueryOperatorPhrase;
 * \endcode
 * Match only documents that contain all of the search terms in sequential order.
 *
 */
@property (nonatomic, assign) LSLocaytaSearchQueryOperator defaultOperator;

/**
 * \brief	The query string to search for.
 *
 * The query string will be parsed into terms, which will be used to perform the
 * actual matching.  Matching documents are returned in order of relevance to the
 * terms of the query string, based on the probabalistic model (unless any sort
 * or balance options are applied).
 *
 * Terms will be reduced to their stemmed form (based on the English stemmer).
 */
@property (nonatomic, copy) NSString *queryString;

/**
 * \brief	Search filters for boolean fields
 *
 * \a filters is a NSDictionary of boolean key/value pairs to filter the query
 * result by.  Filter keys must match a boolean setting specified at 
 * indexing time.
 *
 * Example:
 * \code
 * NSDictionary *searchFilters = [NSDictionary dictionaryWithObjectsAndKeys:
 *                                [NSArray arrayWithObject:@"red"], @"colour",
 *                                [NSArray arrayWithObject:@"small"], @"size",
 *                                nil];
 * searchQuery.filters = searchFilters;
 * \endcode
 */
@property (nonatomic, retain) NSDictionary *filters;

/**
 * \brief	Search filters for numericslot fields
 *
 * \a numericFilters is a NSDictionary of numeric ranges to filter results by.
 * The dictionary is keyed by slot numbers, and the values are arrays of ranges. 
 * Each range is represented as an NSDictionary with 'min' and 'max' keys.
 *
 * Ranges are inclusive at the lower bound and exclusive at the upper bound,
 * ie, <tt>[min...max)</tt> in set notation.
 *
 * This property is exposed for convenience; in practice it is probably
 * simpler to use \ref addNumericRangeFrom:to:forSlot:
 */
@property (nonatomic, retain) NSDictionary *numericFilters;

/**
 * \brief	The balance factor for the text proportion of this query
 *
 * The query tree generated for the \a queryString will be weighted by the factor
 * specified here. This will usually be a number between 0.0 and 1.0, and the
 * default is 1.0.
 *
 * Any boolean filters applied to the query are not affected.
 *
 * This setting is meaningless unless additional balance factors have been
 * provided. See \ref balance_factors.
 */
@property (nonatomic, assign) double balanceFactor;

/**
 * \brief	Set the search balancers
 *
 * \a balancers is a NSArray of LSLocaytaSearchBalance subclass instances, which
 * will be used to apply Locayta Balance Factor calculation on.
 *
 * At query time, the weights returned by each balancer will be mixed in with
 * the calculated text weight of the result. This can be used to balance/bias/boost
 * results based on the value of the balancer for each document.
 * For more information, see \ref balance_factors.
 */
@property (nonatomic, retain) NSArray *balancers;


/**
 * \brief	The search threshold
 *
 * Set the minimum weight to be returned in the search results. This can be
 * useful to remove largely irrelevant results from the bottom of an OR query.
 *
 * Threshold should be a value between 0.0 and 1.0. The default is 0.0, which
 * will cause all results to be returned.
 */
@property (nonatomic, assign) double threshold;
 
/**
 * \brief	Returns an autoreleased instance of LSLocaytaSearchQuery
 * 
 * @param aQueryString the text to use for the search, eg what the user has
 *        typed into the search box.
 *
 * This is a convenience method for [[[LSLocaytaSearchQuery alloc] initWithQueryString:queryString filters:nil] autorelease];
 */
+ (id)queryWithQueryString:(NSString *)aQueryString;

/**
 * \brief	Returns a new instance of LSLocaytaSearchQuery
 * 
 * @param aQueryString the text to use for the search, eg what the user has
 *        typed into the search box.
 *
 * This is a convenience method for
 * \code
 * -[LSLocaytaSearchQuery initWithQueryString:queryString filters:nil]
 * \endcode
 *
 * See initWithQueryString:filters:
 */
- (id)initWithQueryString:(NSString *)aQueryString;

/**
 * \brief	Returns a new instance of LSLocaytaSearchQuery
 *
 * @param aQueryString the text to use for the search, eg what the user has
 *        typed into the search box.
 * @param searchFilters a NSDictionary of boolean key/value pairs to filter the query result
 * by.  Filter keys must match a boolean setting specified at indexing time.
 *
 * The \a queryString and \a searchFilters arguments cannot both be nil (or empty).
 *
 * Example:
 * \code
 * NSDictionary *searchFilters = [NSDictionary dictionaryWithObjectsAndKeys:
 *                                [NSArray arrayWithObject:@"small"], @"size",
 *                                [NSArray arrayWithObject:@"red"], @"colour",
 *                                nil];
 * LSLocaytaSearchQuery *searchQueryWithFilter = [[LSLocaytaSearchQuery alloc] initWithQueryString:@"my search query" filters:searchFilters];
 * \endcode
 */
- (id)initWithQueryString:(NSString *)aQueryString filters:(NSDictionary *)searchFilters;


/**
 * \brief	Returns a description of the parsed query.
 *
 */
- (NSString *)queryDescription;


/**
 * \brief	Add a numeric range filter to the query.
 *
 * @param min The lower end of the range to filter by (inclusive).
 * @param max The upper end of the range to filter by (exclusive).
 * @param slot the numericslot used in the schema to store values for this filter.
 *
 * Ranges are inclusive at the lower bound only, so a range of 10-20 will return
 * documents containing values from 10 up until any value less than 20.
 * This is for consistancy with LSLocaytaSearchResult::convertNumericFacetData:toRanges:
 *
 * This method can be used more than once to add further restrictions.
 * If multiple ranges are given for one slot, it will return documents
 * in any of the ranges. If more than one slot is used, a document must
 * contain valid values for every slot to be considered a match.
 */
- (void)addNumericRangeFrom:(double)min to:(double)max forSlot:(int)slot;

/**
 * \brief	Remove all numeric range filters from the query.
 */
- (void)clearNumericRanges;

@end
