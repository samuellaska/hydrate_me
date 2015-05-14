//
//  EmpaLinkConfig.h
//  EmpaLink
//
//  Created by Alberto Guarino on 11/22/12.
//  Copyright (c) 2012 Empatica. All rights reserved.
//

/*
 
 BVP_DELEGATE
 GSR_DELEGATE
 ACC_DELEGATE
 ST_DELEGATE
 BATT_DELEGATE
 
 IBI_DELEGATE
 
 */

#define FORCE_AUTOMATIC_RECONNECTION NO
#define DISABLE_AUTOMATIC_RECONNECTION YES
#define AUTOMATIC_RECONNECTION_DELAY (15.0)

#define STRESS_BARS_MAX_VALUE (15.0)
#define HRV_TIME_WINDOW (5*60)  // 5 minutes
// TODO: we should probably initialize this from external code
#define STRESS_BARS_PER_HOUR (12.0)  // One every 5 minutes
//#define STRESS_BARS_PER_HOUR (12*60.0)  // One every 5 seconds
#ifndef BAR_DURATION
    #define BAR_DURATION (60 * (60 / STRESS_BARS_PER_HOUR))
#endif

#define AMAZON_MATLAB_URL @"http://184.169.135.131/"
#define SESSIONTYPE_STRESS  10

//#define BACKEND_HOST        @"https://50.18.154.136/"
#define BACKEND_HOST        @"https://www.empatica.com/"
#define BACKEND_INSTANCE    @"empatica_moodtracker/"

#define UPDATE_SESSION_URL  BACKEND_HOST BACKEND_INSTANCE @"update_processed_signal_session.php"

#define SERVICE_NAME        @"EmpaticaRealtime"

#define AUTOMATIC_RECONNECTION_ON_KEY @"AutomaticReconnectionOn"
#define CURRENT_SESSION_ARRAY_KEY @"currentSessionIDArray"

#define SEND_MET_PATH       @"MET_upload-J.php"

// ---- API Modes ----
// User Mode
#define USER_LOGIN_URL              BACKEND_HOST BACKEND_INSTANCE   @"check_app_login-J.php"
#define USER_SAVE_SESSION_URL       BACKEND_HOST BACKEND_INSTANCE   @"new_signal_session.php"
#define USER_UPLOAD_URL             AMAZON_MATLAB_URL               @"empatica/upload_session_chunk.php"
#define CHECK_AUTHENTICATION_URL    BACKEND_HOST BACKEND_INSTANCE   @"check_authentication.php"

// Developer Mode
#define API_VERSION @"IOS_0.6"

#define CONNECT_INSTANCE @"connect/"
#define API_LOGIN_URL           BACKEND_HOST CONNECT_INSTANCE   @"empalink/api_login.php"
#define API_SAVE_SESSION_URL    BACKEND_HOST CONNECT_INSTANCE   @"empalink/api_new_session.php"
#define API_UPLOAD_URL          AMAZON_MATLAB_URL               @"empatica/empalink_upload_session_chunk.php"

// EDIT IF YOU DARE -------------------------------
#define INTERNET_CONNECTION_IS_ALLOWED true

//#define TECHNICOLOR_EDITION

// YOU'D BETTER NOT EDIT -------------------------
#ifdef TECHNICOLOR_EDITION
    #undef INTERNET_CONNECTION_IS_ALLOWED
    #define INTERNET_CONNECTION_IS_ALLOWED false
    #undef CONNECTION_OPTIONS_ARE_ALLOWED
    #define CONNECTION_OPTIONS_ARE_ALLOWED true
    #warning TECHNICOLOR edition
#endif

#if (INTERNET_CONNECTION_IS_ALLOWED)
    #define HARVEST_AND_UPLOAD_SESSIONS true
#else
    #define HARVEST_AND_UPLOAD_SESSIONS false
#endif

#if (HARVEST_AND_UPLOAD_SESSIONS)
    #warning session upload ENABLED
#else
    #warning session upload DISABLED
#endif



