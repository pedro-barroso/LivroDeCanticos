//
//  LSLocaytaSearchBalanceDistance.h
//  LocaytaSearch
//
//  Created by Nick Murdoch on 12/07/2012.
//  Copyright (c) 2012 Locayta Limited. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LSLocaytaSearchBalancer.h"

@class LSDistanceWeightingSystem;

@interface LSLocaytaSearchBalanceDistance : LSLocaytaSearchBalancer {

}

- (id)initWithFactor:(double)balanceFactor slot:(int)slot latLong:(NSString *)latLong;
- (id)initWithFactor:(double)balanceFactor slot:(int)slot latitude:(double)latitude longitude:(double)longitude;

@end
