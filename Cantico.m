//
//  Cantico.m
//  LivroDeCanticos
//
//  Created by Pedro Barroso on 22/08/13.
//  Copyright (c) 2013 Pedro Barroso. All rights reserved.
//

#import "Cantico.h"

@interface Cantico ()

@end

@implementation Cantico
@synthesize canticoText, canticoTitulo, canticoNum;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    //canticoNum = 20;

    canticoNum++;
    
    NSLog(@"Numero do cantico: %i", canticoNum);
    NSLog([@"Titulo do cantico: " stringByAppendingString: canticoTitulo]);
    
    // lê ficheiro do texto seleccionado
    NSString* path = [[NSBundle mainBundle] pathForResource:[@"c" stringByAppendingString: [NSString stringWithFormat:@"%d", canticoNum]]
                                                     ofType:@"txt"];
    NSString* content = [NSString stringWithContentsOfFile:path
                                                  encoding:NSUTF8StringEncoding
                                                     error:NULL];
    int i = 0;
    NSString* texto = @"";
    for (NSString *line in [content componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]]) {
        if (i == 0){
            self.title = line;
            CGRect frame = CGRectMake(0, 0, [self.title sizeWithFont:[UIFont boldSystemFontOfSize:10.0]].width, 44);
            UILabel *label = [[UILabel alloc] initWithFrame:frame];
            label.backgroundColor = [UIColor clearColor];
            label.textColor = [UIColor whiteColor];
            label.font = [UIFont fontWithName:@"Arial-BoldMT" size:15];
            label.textAlignment = UITextAlignmentCenter;
            self.navigationItem.titleView = label;
            label.text = self.title;
            i++;
        }
        if (i == 1){
            i++;
        }
        else{
            texto = [texto stringByAppendingString:line];
            texto = [texto stringByAppendingString:@"\n"];
            i++;
        }
    }
    
    canticoText.text = texto;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
