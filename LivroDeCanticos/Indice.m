//
//  Indice.m
//  LivroDeCanticos
//
//  Created by Pedro Barroso on 22/08/13.
//  Copyright (c) 2013 Pedro Barroso. All rights reserved.
//

#import "Indice.h"
#import "Cantico.h"

@interface Indice ()

@end

@implementation Indice
@synthesize indiceArray;

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = @"Indice";

    indiceArray = [[NSMutableArray alloc]init];
    int i = 0;
    NSString* path = [[NSBundle mainBundle] pathForResource:@"indice"
                                                     ofType:@"txt"];

    NSString *fileContents = [NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:NULL];
    
    for (NSString *line in [fileContents componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]]) {
        if (![line isEqualToString:@""]) {
            [indiceArray insertObject:line atIndex:i];
            i++;
        }
        
    }    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return indiceArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    //Create an NSString object that we can use as the reuse identifier
    static NSString *CellIdentifier = @"Cell";
    
    //Check to see if we can reuse a cell from a row that has just rolled off the screen
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    //If there are no cells to be reused, create a new cell
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    //Set the text attribute to whatever we are currently looking at in our array
    cell.textLabel.text = [indiceArray objectAtIndex:indexPath.row];
    
    //Set the detail disclosure indicator
    cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    
    cell.textLabel.font = [UIFont fontWithName:@"ChalkboardSE-Bold" size:15];
    
    //Return the cell
    return cell;

}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    //Create a DetailViewController Object
    Cantico * cant = [[Cantico alloc]init];
    
    //Set DVC to the destinationViewController property of the segue
    cant = [segue destinationViewController];
    
    
    //Get the indexpath
    NSIndexPath * path = [self.tableView indexPathForSelectedRow];
    
    NSString * titulo = [indiceArray objectAtIndex:path.row];
    
    cant.canticoNum = path.row;
    cant.canticoTitulo = titulo;
}
@end
