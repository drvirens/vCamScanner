//
//  kConstDefine.h
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#ifndef demoCode_kConstDefine_h
#define demoCode_kConstDefine_h

// HELP MARCO for convert number command to string,for use of ccnotifycenter's observer
// command need string,and send to server's command is number
// p.s.need wrap by STRING_FY marco ,if use cmd2str directly,it will stringfy the param
// name by default
#define CMD2STR(cmd) #cmd
#define STRING_FY(x) CMD2STR(x)

#define TEST_CMD_REGISTER   2801
#define TEST_CMD_DELETE     2802
#define TEST_CMD_MODIFY     2803
#define TEST_CMD_QUERY      2806
#define TEST_CMD_OP_SUCCESS 1001
#define TEST_CMD_OP_FAILED  1002

#define KLOGINSCENE_TAG     0
#define KNORMALMAP_TAG      1
#define KFBMAP_TAG          2
#define KACTIVITYMAP_TAG    3
#define KLOADINGSCENE_TAG   4
#define KCREATEROLE_TAG     5

// THE MORE SMALLER VALUE,THE MORE HIGHER TOUCH PRIORITY
// FOR EXAMPLE,MENU is -128
#define TOUCH_PRIORITY_MAPVIEW      80
#define TOUCH_PRIORITY_MAINVIEW     76
#define TOUCH_PRIORITY_UIVIEW       72
#define TOUCH_PRIORITY_MESSAGEBOX   68

#endif
