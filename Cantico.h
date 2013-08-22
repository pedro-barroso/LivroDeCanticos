//
//  Cantico.h
//  LivroDeCanticos
//
//  Created by Pedro Barroso on 22/08/13.
//  Copyright (c) 2013 Pedro Barroso. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface Cantico : UIViewController
@property (weak, nonatomic) IBOutlet UITextView *canticoText;
@property(nonatomic, strong) NSString * canticoTitulo;
@property int canticoNum;

@end
