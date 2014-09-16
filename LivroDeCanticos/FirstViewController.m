//
//  FirstViewController.m
//  LivroDeCanticos
//
//  Created by Pedro Barroso on 22/08/13.
//  Copyright (c) 2013 Pedro Barroso. All rights reserved.
//

#import "FirstViewController.h"
#import "Cantico.h"

@interface FirstViewController ()

@end

@implementation FirstViewController
@synthesize procura, texto, select;
- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    self.title = @"Pesquisa";
    [procura displaysSearchBarInNavigationBar];
     NSLog(@"Pesquisa");
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)searchBarSearchButtonClicked:(UISearchBar *)searchBar
{
    [self handleSearch:searchBar];
    NSLog(@"User searched for %@", searchBar.text);

}

- (void)handleSearch:(UISearchBar *)searchBar
{
    NSLog(@"User searched for %@", searchBar.text);
    [searchBar resignFirstResponder]; // if you want the keyboard to go away
    
    texto = searchBar.text;
}

- (void)searchBarCancelButtonClicked:(UISearchBar *) searchBar
{
    NSLog(@"User canceled search");
    [searchBar resignFirstResponder]; // if you want the keyboard to go away
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    NSLog(@"Aqui");
    if(select.selectedSegmentIndex == 0){
        if (texto.intValue > 0 && texto.intValue < 151) {
            //Create a DetailViewController Object
            Cantico * cant = [[Cantico alloc]init];
            
            //Set DVC to the destinationViewController property of the segue
            cant = [segue destinationViewController];
            
            cant.canticoNum =texto.intValue;
        }
    }else{
        // procura por texto
    }
    
}
@end
