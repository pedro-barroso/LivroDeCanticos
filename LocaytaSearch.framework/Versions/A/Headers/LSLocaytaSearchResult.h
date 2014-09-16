//
//  LocaytaSearchResult.h
//  LocaytaSearch
//
//  Created by Chris Miles on 19/04/10.
//  Copyright 2010-2011 Locayta Limited. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * \brief	Represents the result of a successful search query.
 *
 * Contains metadata about the query, such as how many documents were matched,
 * how many were returned, whether the search query was spell corrected, etc.
 *
 * The actual search results are available in the \ref results array.
 */
@interface LSLocaytaSearchResult : NSObject {
    NSString *requestedQueryString;
    NSString *correctedQueryString;
    NSString *suggestedQueryString;
    NSSet *queryTerms;
    BOOL wasAutoSpellCorrected;
    
    NSInteger itemCount;
    NSInteger matchCount;
    BOOL matchCountExact;
    NSArray *results;
    NSDictionary *facets;
    
    NSSet *_rawQueryTerms;
    NSDictionary *_unstemMapping;
}

/**
 * \brief	The query string given to the search request.
 */
@property (nonatomic, copy, readonly) NSString *requestedQueryString;

/**
 * \brief	The query string actually used if the requested query was automatically spell corrected.
 *
 * \ref wasAutoSpellCorrected will be YES if this property contains a useful value.
 */ 
@property (nonatomic, copy, readonly) NSString *correctedQueryString;

/**
 * \brief	Suggested query spelling if spell suggestions was requested.
 *
 */ 
@property (nonatomic, copy, readonly) NSString *suggestedQueryString;

/**
 * \brief	Set of all terms used to perform the search query.
 *
 */ 
@property (nonatomic, retain, readonly) NSSet *queryTerms;

/**
 * \brief	Only YES iff auto spell correction was requested and the requested query was corrected.
 *
 * The actual query used will be available in the \ref correctedQueryString property.
 */ 
@property (nonatomic, assign, readonly) BOOL wasAutoSpellCorrected;

/**
 * \brief	The number of items returned in this result set.
 *
 */
@property (nonatomic, assign, readonly) NSInteger itemCount;

/**
 * \brief	The number of records matched by the search query.
 *
 * May be an estimation, see \ref matchCountExact.
 */ 
@property (nonatomic, assign, readonly) NSInteger matchCount;

/**
 * \brief	If YES then \ref matchCount is exact, otherwise \ref matchCount is only an estimation (for performance reasons).
 *
 */ 
@property (nonatomic, assign, readonly) BOOL matchCountExact;

/**
 * \brief	An array of search results matching the search query.
 * 
 * Each result in the results array is a NSDictionary containing the following keys:
 *
 * - docid (NSNumber) : internal reference number of the document (this is not the user-defined ID value).
 * - weight (NSNumber) : the relevance of the result with respect to the search query, between 0.0 and 1.0.
 * - fields (NSDictionary) : a dictionary of fieldname/array pairs from the stored record. These are all the fields
 * that were indexed with the "field" indexing option (see \subpage schema).  Each field value is an NSArray of one or more
 * NSStrings.  Multiple strings are returned when a field is specified more than once in a record at
 * index time.
 *
 * Example of a search result:
 *
 * \code
 * searchResult.results: (
 *    {
 *        docid = 1;
 *        fields = {
 *            "cost_dollar" = (
 *                "1200"
 *            );
 *            "country" = (
 *                "UK"
 *            );
 *            "id" = (
 *                "ABCDB20099-0"
 *            );
 *            "title" = (
 *                "Industry Report - UK - May 2008"
 *            );
 *        };
 *        weight = 0.3774427;
 *    }
 * )
 * \endcode
 */
@property (nonatomic, retain, readonly) NSArray *results;

/**
 * \brief	A dictionary of facets generated from the search results.
 *
 * These will be presented as a dictionary containing NSString and NSNumber
 * keys (for boolean and slot facets, respectively). The values will also be
 * dictionaries, containing NSString or NSNumber keys (NSString for most facets;
 * NSNumber for facets requested from numeric slots). The values of these
 * subdictionaries will be NSNumber objects representing the number of items
 * found in the current search results for the given facet option.
 *
 * Example of some facets:
 *
 * \code
 * searchResults.facets: {
 *   XXCA =     {
 *       Business = 1;
 *       industrial = 1;
 *   };
 *   2 =     {
 *       UK = 1;
 *   };
 *   1 =     {
 *       600 = 1;
 *   };
 * }
 * \endcode
 */
@property (nonatomic, retain, readonly) NSDictionary *facets;

/**
 * \brief Transform numeric facet data into a set of ranges.
 * 
 * The ranges will be equal in size (eg 10-20, 20-30, 30-40), although not
 * necessarily contiguous.
 *
 * Ranges are returned as dictionaries with the keys "from", "to", and "count".
 * The "from" and "to" values are NSNumber-wrapped doubles representing the bounds of the range.
 * "from" is inclusive while "to" is exclusive. The "count" value is an NSNumber-wrapped
 * int representing the number of items combined into this range.
 *
 * @param facetData an NSDictionary in the form provided by #facets.
 * @param maxRanges the maximum number of ranges to generate. The actual number
 *                  of ranges generated may be lower.
 *
 * Example:
 *
 * \code
 * rangedFacetOptions = [LSLocaytaSearchResult convertNumericFacetData:[result.facets objectForKey:[NSNumber numberWithInt:3]] toRanges:5];
 * \endcode
 */
+ (NSArray *) convertNumericFacetData:(NSDictionary *)facetData toRanges:(int)maxRanges;

/**
 * \brief Transform numeric facet data into a set of ranges with similar counts.
 *
 * The ranges will not necessarily be equal in size (eg, 1-10, 10-50, 50-100),
 * but the function will attempt to distribute them such that they have similar
 * counts within each range.
 *
 * Ranges are returned as dictionaries with the keys "from", "to", and "count".
 * The "from" and "to" values are NSNumber-wrapped doubles representing the bounds of the range.
 * "from" is inclusive while "to" is exclusive. The "count" value is an NSNumber-wrapped
 * int representing the number of items combined into this range.
 *
 * @param facetData an NSDictionary in the form provided by #facets.
 * @param maxRanges the maximum number of ranges to generate. The actual number
 *                  of ranges generated may be lower.
 *
 * Example:
 *
 * \code
 * rangedFacetOptions = [LSLocaytaSearchResult convertNumericFacetData:[result.facets objectForKey:[NSNumber numberWithInt:3]] toDistributedRanges:5];
 * \endcode
 */
+ (NSArray *) convertNumericFacetData:(NSDictionary *)facetData toDistributedRanges:(int)maxRanges;

/**
 * \brief Transform numeric facet data into a set of defined ranges.
 *
 * @param facetData an NSDictionary in the form provided by #facets.
 * @param ranges An NSArray of dictionaries with the keys "from" and "to".
 *               The "from" and "to" values are NSNumber-wrapped doubles
 *               representing the bounds of the range.
 *               "from" is inclusive while "to" is exclusive.
 *               One or both of "from" and "to" may be nil to indicate an
 *               unbounded range.
 * @return An NSArray with the same (copied) dictionaries as the ranges parameter,
 *         with each dictionary given an additional key "count", which contains
 *         the aggregated count of all items that fit into the range.
 *
 * Example:
 *
 * \code
 * NSArray *ranges = [NSArray arrayWithObjects:
 *                      [NSDictionary dictionaryWithObjectsAndKeys:
 *                          [NSNumber numberWithDouble:0.0], @"from",
 *                          [NSNumber numberWithDouble:10.0], @"to",
 *                           nil],
 *                      [NSDictionary dictionaryWithObjectsAndKeys:
 *                          [NSNumber numberWithDouble:10.0], @"from",
 *                          [NSNumber numberWithDouble:20.0], @"to",
 *                           nil],
 *                      nil];
 * rangedFacetOptions = [LSLocaytaSearchResult convertNumericFacetData:[result.facets objectForKey:[NSNumber numberWithInt:3]]
 *                                                       toFixedRanges:ranges];
 * \endcode
 */
+ (NSArray *) convertNumericFacetData:(NSDictionary *)facetData toFixedRanges:(NSArray *)ranges;

@end
