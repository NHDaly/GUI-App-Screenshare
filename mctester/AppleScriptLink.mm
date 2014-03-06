//
//  AppleScriptLink.cpp
//  MultiComputer Tester
//
//  Created by Nathan Daly on 7/29/13.
//  Copyright (c) 2013 Lions Entertainment. All rights reserved.
//

#include "AppleScriptLink.h"

using namespace std;

const char * AppTellStr = "set currentPosition to missing value\n"
                          "tell application \"System Events\" to tell application process ";

const char * GetPosStr = "set currentPosition to (position of window 1)\n"
                         "end tell\n"
                         "return currentPosition\n";

const char * GetSizeStr = "set currentSize to (size of window 1)\n"
                          "end tell\n"
                          "return currentSize\n";


void getWindowPosition(const string &appname, int &outX, int &outY) {
    
    NSDictionary *error = nil;
    
    string appCommandName = "\"" + appname + "\"\n";
    
    NSMutableString *scriptText = [NSMutableString stringWithUTF8String:AppTellStr];
    [scriptText appendString:[NSString stringWithUTF8String:appCommandName.c_str()]];
    [scriptText appendString:[NSMutableString stringWithUTF8String:GetPosStr]];
    
    NSAppleScript *script = [[[NSAppleScript alloc] initWithSource:scriptText] autorelease];
    
    NSAppleEventDescriptor *result = [script executeAndReturnError:&error];
    
//    DescType descriptorType = [result descriptorType];
//    NSLog(@"descriptorType == %@", NSFileTypeForHFSTypeCode(descriptorType));

    // returns a list of 2 elements
    NSData *dataX = [[result descriptorAtIndex:1] data];
    NSData *dataY = [[result descriptorAtIndex:2] data];

    [dataX getBytes:&outX length:[dataX length]];
    [dataY getBytes:&outY length:[dataY length]];
        
}


void getWindowSize(const string &appname, int &outW, int &outH) {
        
        NSDictionary *error = nil;
        
        string appCommandName = "\"" + appname + "\"\n";
        
        NSMutableString *scriptText = [NSMutableString stringWithUTF8String:AppTellStr];
        [scriptText appendString:[NSString stringWithUTF8String:appCommandName.c_str()]];
        [scriptText appendString:[NSMutableString stringWithUTF8String:GetSizeStr]];
    
        NSAppleScript *script = [[NSAppleScript alloc] initWithSource:scriptText];
        
        NSAppleEventDescriptor *result = [script executeAndReturnError:&error];
    
        [script release];
    
//        DescType descriptorType = [result descriptorType];
//        NSLog(@"descriptorType == %@", NSFileTypeForHFSTypeCode(descriptorType));
    
        // returns a list of 2 elements
        NSData *dataW = [[result descriptorAtIndex:1] data];
        NSData *dataH = [[result descriptorAtIndex:2] data];
                
        [dataW getBytes:&outW length:[dataW length]];
        [dataH getBytes:&outH length:[dataH length]];
                
    }
