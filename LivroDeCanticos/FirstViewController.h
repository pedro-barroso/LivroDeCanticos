//
//  FirstViewController.h
//  LivroDeCanticos
//
//  Created by Pedro Barroso on 22/08/13.
//  Copyright (c) 2013 Pedro Barroso. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FirstViewController : UIViewController
@property (weak, nonatomic) IBOutlet UISearchDisplayController *procura;
@property (weak, nonatomic) IBOutlet UISegmentedControl *select;
//@property (weak, nonatomic) IBOutlet UILabel *label;
@property (strong, nonatomic) NSString *texto;
@end
