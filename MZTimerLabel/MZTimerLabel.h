//
//  MZTimerLabelWatch.h
//  Version 0.5.1
//  Created by MineS Chan on 2013-10-16
//  Updated 2014-12-15

// This code is distributed under the terms and conditions of the MIT license.

// Copyright (c) 2014 MineS Chan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <WatchKit/WatchKit.h>


/**********************************************
 MZTimerLabelWatch TimerType Enum
 **********************************************/
typedef enum{
    MZTimerLabelWatchTypeStopWatch,
    MZTimerLabelWatchTypeTimer
}MZTimerLabelWatchType;

/**********************************************
 Delegate Methods
 @optional

 - timerLabel:finshedCountDownTimerWithTimeWithTime:
    ** MZTimerLabelWatch Delegate method for finish of countdown timer

 - timerLabel:countingTo:timertype:
    ** MZTimerLabelWatch Delegate method for monitering the current counting progress

 - timerlabel:customTextToDisplayAtTime:
    ** MZTimerLabelWatch Delegate method for overriding the text displaying at the time, implement this for your very custom display formmat
**********************************************/

@class MZTimerLabelWatch;
@protocol MZTimerLabelWatchDelegate <NSObject>
@optional
-(void)timerLabel:(MZTimerLabelWatch*)timerLabel finshedCountDownTimerWithTime:(NSTimeInterval)countTime;
-(void)timerLabel:(MZTimerLabelWatch*)timerLabel countingTo:(NSTimeInterval)time timertype:(MZTimerLabelWatchType)timerType;
-(NSString*)timerLabel:(MZTimerLabelWatch*)timerLabel customTextToDisplayAtTime:(NSTimeInterval)time;
@end

/**********************************************
 MZTimerLabelWatch Class Defination
 **********************************************/

@interface MZTimerLabelWatch : NSObject;

/*Delegate for finish of countdown timer */
@property (nonatomic,weak) id<MZTimerLabelWatchDelegate> delegate;

/*Time format wish to display in label*/
@property (nonatomic,copy) NSString *timeFormat;

/*Target label object*/
@property (nonatomic,strong) WKInterfaceLabel *timeLabel;

/*Type to choose from stopwatch or timer*/
@property (assign) MZTimerLabelWatchType timerType;

/*Is The Timer Running?*/
@property (assign,readonly) BOOL counting;

/*Do you want to reset the Timer after countdown?*/
@property (assign) BOOL resetTimerAfterFinish;

/*Do you want the timer to count beyond the HH limit from 0-23 e.g. 25:23:12 (HH:mm:ss) */
@property (assign,nonatomic) BOOL shouldCountBeyondHHLimit;

#if NS_BLOCKS_AVAILABLE
@property (copy) void (^endedBlock)(NSTimeInterval);
#endif


/*--------Init methods to choose*/
-(id)initWithLabel:(WKInterfaceLabel*)theLabel andTimerType:(MZTimerLabelWatchType)theType;
-(id)initWithLabel:(WKInterfaceLabel*)theLabel;


/*--------Timer control methods to use*/
-(void)start;

#if NS_BLOCKS_AVAILABLE
-(void)startWithEndingBlock:(void(^)(NSTimeInterval countTime))end; //use it if you are not going to use delegate
#endif

-(void)pause;
-(void)reset;

/*--------Setter methods*/
-(void)setCountDownTime:(NSTimeInterval)time;
-(void)setStopWatchTime:(NSTimeInterval)time;
-(void)setCountDownToDate:(NSDate*)date;

-(void)addTimeCountedByTime:(NSTimeInterval)timeToAdd;

/*--------Getter methods*/
- (NSTimeInterval)getTimeCounted;
- (NSTimeInterval)getTimeRemaining;
- (NSTimeInterval)getCountDownTime;


@end
