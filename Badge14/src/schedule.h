/* 
 * File:   schedule.h
 * Author: morgan
 *
 * Created on May 25, 2014, 8:12 PM
 */

#ifndef SCHEDULE_H
#define	SCHEDULE_H

struct Conference_Event
{
    unsigned int start_time, end_time;
    char title[128];
    //char description[256];
};
#define NUM_EVENTS 21
struct Conference_Event conf_events[NUM_EVENTS];
void initConferenceEvents()
{
    //8:00	9:00	Breakfast
    conf_events[0].start_time = 80000;
    conf_events[0].end_time = 90000;
    b_strcpy(conf_events[0].title, "Breakfast");

    //9:00	9:10	Welcome
    conf_events[1].start_time = 90000;
    conf_events[1].end_time = 91000;
    b_strcpy(conf_events[1].title, "Welcome");

    //9:10	10:10	David Kennedy Keynote
    conf_events[2].start_time = 91000;
    conf_events[2].end_time = 101000;
    b_strcpy(conf_events[2].title, "Keynote (David Kennedy)");

    //10:10	10:30	Break
    conf_events[3].start_time = 101000;
    conf_events[3].end_time = 103000;
    b_strcpy(conf_events[3].title, "Break");

    //10:30	10:40	Nick Popovich & Steve Passino
        //CTF Intro
    conf_events[4].start_time = 103000;
    conf_events[4].end_time = 104000;
    b_strcpy(conf_events[4].title, "Nick & Steve");


    //10:40	10:50	Morgan Stuart & Paul Bruggeman
        //Badge Intro
    conf_events[5].start_time = 104000;
    conf_events[5].end_time = 105000;
    b_strcpy(conf_events[5].title, "Morga & Paul");

    //11:00	12:00	Kizz MyAnthia
        //Into The Worm Hole: Metasploit For Web PenTesting
    conf_events[6].start_time = 110000;
    conf_events[6].end_time = 120000;
    b_strcpy(conf_events[6].title, "Kizz MyAnthia");

    //12:00	1:00	Lunch
    conf_events[7].start_time = 120000;
    conf_events[7].end_time = 10000;
    b_strcpy(conf_events[7].title, "Lunch");

    //1:00	1:50	Ben Tomhave
        //How to Achieve Success with Cyber Risk Assessment and Analysis
    conf_events[8].start_time = 10000;
    conf_events[8].end_time = 15000;
    b_strcpy(conf_events[8].title, "Ben Tomhave");

    //Nick Popovich
    //I Found a Thing and You Can Too: ISP’s Unauthenticated SOAP Service = Find (almost) All the Things!	CTF Prep
    conf_events[9].start_time = 10000;
    conf_events[9].end_time = 15000;
    b_strcpy(conf_events[9].title, "Nick Popovich");

    //1:50	2:00	Break 	 	CTF Prep
    conf_events[10].start_time = 15000;
    conf_events[10].end_time = 20000;
    b_strcpy(conf_events[10].title, "Break");

    //2:00	2:50	Jayson E. Street
        //The Hacker In The Fun House Mirror (A Talk On Skewed Perspectives	
    conf_events[11].start_time = 20000;
    conf_events[11].end_time = 25000;
    b_strcpy(conf_events[11].title, "Jayson E. Street");

    //mubix
    //Attacker Ghost Stories: Mostly Free Defenses That Gives Attackers Nightmares	CTF Prep
    conf_events[12].start_time = 20000;
    conf_events[12].end_time = 25000;
    b_strcpy(conf_events[12].title, "mubix");

    //2:50	3:00	Break 	 	CTF Prep
    conf_events[13].start_time = 25000;
    conf_events[13].end_time = 30000;
    b_strcpy(conf_events[13].title, "Break");


    //3:00	3:50	Inga Goddijn
        //Cyber Insurance – Worth the Effort or Total Ripoff?	
    conf_events[14].start_time = 30000;
    conf_events[14].end_time = 35000;
    b_strcpy(conf_events[14].title, "Inga Goddin");
    
    //Jack Mannino & Abdullah Munawar
    //How To Find Mobile Internet Love	CTF Prep
    conf_events[15].start_time = 30000;
    conf_events[15].end_time = 35000;
    b_strcpy(conf_events[15].title, "Jack and Abdullah");

    //3:50	4:00	Break 	 	CTF Prep
    conf_events[16].start_time = 35000;
    conf_events[16].end_time = 40000;
    b_strcpy(conf_events[16].title, "Break");


    //4:00	4:50	Seth Hanford
       //CVSS v3 – This One Goes to 11
    conf_events[17].start_time = 40000;
    conf_events[17].end_time = 45000;
    b_strcpy(conf_events[17].title, "Seth Hanford");

    //4:50	5:00	Break
    conf_events[18].start_time = 45000;
    conf_events[18].end_time = 50000;
    b_strcpy(conf_events[18].title, "Break");

    //5:00	5:50	Schuyler Towne
    //How To Make A Lock
    conf_events[19].start_time = 50000;
    conf_events[19].end_time = 55000;
    b_strcpy(conf_events[19].title, "Schuyler Towne");

    //5:50	6:00	Closing
    conf_events[20].start_time = 55000;
    conf_events[20].end_time = 60000;
    b_strcpy(conf_events[20].title, "Closing");

    //6:30	8:30	After Party Sponsored by FishNet Security, Rapid7 & LogRhythm at Postbellum!

}

/*
Start	End	Commonwealth Ballroom	Richmond Salons	Other
8:00		Registration
8:00	9:00	Breakfast
9:00	9:10	Welcome
9:10	10:10	David Kennedy
Keynote
10:10	10:30	Break
10:30	10:40	Nick Popovich & Steve Passino
CTF Intro
10:40	10:50	Morgan Stewart & Paul Bruggeman
Badge Intro
10:50	11:00	Break
11:00	12:00	Kizz MyAnthia
Into The Worm Hole: Metasploit For Web PenTesting
12:00	1:00	Lunch
1:00	1:50	Ben Tomhave
How to Achieve Success with Cyber Risk Assessment and Analysis	Nick Popovich
I Found a Thing and You Can Too: ISP’s Unauthenticated SOAP Service = Find (almost) All the Things!	CTF Prep
1:50	2:00	Break 	 	CTF Prep
2:00	2:50	Jayson E. Street
The Hacker In The Fun House Mirror (A Talk On Skewed Perspectives	mubix
Attacker Ghost Stories: Mostly Free Defenses That Gives Attackers Nightmares	CTF Prep
2:50	3:00	Break 	 	CTF Prep
3:00	3:50	Inga Goddijn
Cyber Insurance – Worth the Effort or Total Ripoff?	Jack Mannino & Abdullah Munawar
How To Find Mobile Internet Love	CTF Prep
3:50	4:00	Break 	 	CTF Prep
4:00	4:50	Seth Hanford
CVSS v3 – This One Goes to 11
4:50	5:00	Break
5:00	5:50	Schuyler Towne
How To Make A Lock
5:50	6:00	Closing
6:30	8:30	After Party Sponsored by FishNet Security, Rapid7 & LogRhythm at Postbellum! 
 */



#endif	/* SCHEDULE_H */

