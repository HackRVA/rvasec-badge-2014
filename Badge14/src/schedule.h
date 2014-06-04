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
    b_rtccTime start_tm, end_tm;
    unsigned int start_time, end_time;
    //char title[64];
    char ballroom_title[48];
    char salon_title[48];
    char other_title[32];
};

#define NUM_EVENTS_D1 19
#define NUM_EVENTS_D2 17
struct Conference_Event conf_events_d1[NUM_EVENTS_D1],
                        conf_events_d2[NUM_EVENTS_D2];
void initConferenceEvents()
{
    init_d1();
    init_d2();
}


void init_d1(void)
{
    unsigned char i = 0;

    //8:00	9:00	Breakfast
    conf_events_d1[i].start_time = 80000;
    conf_events_d1[i].end_time = 90000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Breakfast");

    //9:00	9:10	Welcome
    conf_events_d1[i].start_time = 90000;
    conf_events_d1[i].end_time = 91000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Welcome");

    //9:10	10:10	David Kennedy Keynote
    conf_events_d1[i].start_time = 91000;
    conf_events_d1[i].end_time = 101000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "David Kennedy (Keynote)");

    //10:10	10:30	Break
    conf_events_d1[i].start_time = 101000;
    conf_events_d1[i].end_time = 103000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Break");

    //10:30	10:40	Nick Popovich & Steve Passino
        //CTF Intro
    conf_events_d1[i].start_time = 103000;
    conf_events_d1[i].end_time = 104000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Nick & Steve");


    //10:40	10:50	Morgan Stuart & Paul Bruggeman
        //Badge Intro
    conf_events_d1[i].start_time = 104000;
    conf_events_d1[i].end_time = 105000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Morgan & Paul");
    //b_strcpy(conf_events_d1[5].title, "Badge Info:  Morgan & Paul");

    //11:00	12:00	Kizz MyAnthia
        //Into The Worm Hole: Metasploit For Web PenTesting
    conf_events_d1[i].start_time = 110000;
    conf_events_d1[i].end_time = 120000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Jayson E. Street");

    //12:00	1:00	Lunch
    conf_events_d1[i].start_time = 120000;
    conf_events_d1[i].end_time = 10000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Lunch");

    //1:00	1:50	Ben Tomhave
        //How to Achieve Success with Cyber Risk Assessment and Analysis
    conf_events_d1[i].start_time = 10000;
    conf_events_d1[i].end_time = 15000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "Nick Popovich");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Ben Tomhave");

    //Nick Popovich
    //I Found a Thing and You Can Too: ISP’s Unauthenticated SOAP Service = Find (almost) All the Things!	CTF Prep
//    conf_events_d1[i].start_time = 10000;
//    conf_events_d1[i].end_time = 15000;
//    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
//    b_strcpy(conf_events_d1[i].salon_title, "\0");
//    b_strcpy(conf_events_d1[i++].ballroom_title, "Nick Popovich");

    //1:50	2:00	Break 	 	CTF Prep
    conf_events_d1[i].start_time = 15000;
    conf_events_d1[i].end_time = 20000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Break");

    //2:00	2:50	Jayson E. Street
        //The Hacker In The Fun House Mirror (A Talk On Skewed Perspectives
    conf_events_d1[i].start_time = 20000;
    conf_events_d1[i].end_time = 25000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "mubix");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Brian Baskin");

    //mubix
    //Attacker Ghost Stories: Mostly Free Defenses That Gives Attackers Nightmares	CTF Prep
//    conf_events_d1[i].start_time = 20000;
//    conf_events_d1[i].end_time = 25000;
//    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
//    b_strcpy(conf_events_d1[i].salon_title, "\0");
//    b_strcpy(conf_events_d1[i++].ballroom_title, "mubix");

    //2:50	3:00	Break 	 	CTF Prep
    conf_events_d1[i].start_time = 25000;
    conf_events_d1[i].end_time = 30000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Break");


    //3:00	3:50	Inga Goddijn
        //Cyber Insurance – Worth the Effort or Total Ripoff?
    conf_events_d1[i].start_time = 30000;
    conf_events_d1[i].end_time = 35000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "Jack and Abdullah");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Inga Goddin");

    //Jack Mannino & Abdullah Munawar
    //How To Find Mobile Internet Love	CTF Prep
//    conf_events_d1[i].start_time = 30000;
//    conf_events_d1[i].end_time = 35000;
//    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
//    b_strcpy(conf_events_d1[i].salon_title, "\0");
//    b_strcpy(conf_events_d1[i++].ballroom_title, "Jack and Abdullah");

    //3:50	4:00	Break 	 	CTF Prep
    conf_events_d1[i].start_time = 35000;
    conf_events_d1[i].end_time = 40000;
    b_strcpy(conf_events_d1[i].other_title, "CTF Prep");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Break");


    //4:00	4:50	Seth Hanford
       //CVSS v3 – This One Goes to 11
    conf_events_d1[i].start_time = 40000;
    conf_events_d1[i].end_time = 45000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Seth Hanford");

    //4:50	5:00	Break
    conf_events_d1[i].start_time = 45000;
    conf_events_d1[i].end_time = 50000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Break");

    //5:00	5:50	Schuyler Towne
    //How To Make A Lock
    conf_events_d1[i].start_time = 50000;
    conf_events_d1[i].end_time = 55000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Schuyler Towne");

    //5:50	6:00	Closing
    conf_events_d1[i].start_time = 55000;
    conf_events_d1[i].end_time = 60000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Closing");

    //6:30	8:30	After Party Sponsored by FishNet Security, Rapid7 & LogRhythm at Postbellum!
    conf_events_d1[i].start_time = 63000;
    conf_events_d1[i].end_time = 83000;
    b_strcpy(conf_events_d1[i].other_title, "\0");
    b_strcpy(conf_events_d1[i].salon_title, "\0");
    b_strcpy(conf_events_d1[i++].ballroom_title, "Postbellum after party!");
}


void init_d2(void)
{
    unsigned char i = 0;

    //8:00	6:00	Registration
    conf_events_d2[i].start_time = 80000;
    conf_events_d2[i].end_time = 60000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Registration");

    //8:00	8:50	Breakfast sponsored by TruShield Security!
    conf_events_d2[i].start_time = 80000;
    conf_events_d2[i].end_time = 85000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Breakfast");

    //8:50	9:00	Welcome
    conf_events_d2[i].start_time = 85000;
    conf_events_d2[i].end_time = 90000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Welcome");

    //9:00	10:00	Gene Fishel
    conf_events_d2[i].start_time = 90000;
    conf_events_d2[i].end_time = 100000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Gene Fishel (Keynote)");

    //10:00	10:10	Break 	 	CTF
    conf_events_d2[i].start_time = 100000;
    conf_events_d2[i].end_time = 101000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Break");

    //10:10	11:00	Evan Booth
    //Terminal Cornucopia: Demystifying the Mullet	  	CTF
    conf_events_d2[i].start_time = 101000;
    conf_events_d2[i].end_time = 110000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Evan Booth");

    //11:00	11:10	Break 	 	CTF
    conf_events_d2[i].start_time = 110000;
    conf_events_d2[i].end_time = 111000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Break");

    //11:10	12:00	Jonathan Dambrot
    conf_events_d2[i].start_time = 111000;
    conf_events_d2[i].end_time = 120000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "Steve Werby");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Jonathan Dambrot");

    conf_events_d2[i].start_time = 120000;
    conf_events_d2[i].end_time = 10000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Lunch");

    conf_events_d2[i].start_time = 10000;
    conf_events_d2[i].end_time = 15000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "Ray Kelly");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Carmen & Kimberley");

    conf_events_d2[i].start_time = 15000;
    conf_events_d2[i].end_time = 20000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Break");

    conf_events_d2[i].start_time = 20000;
    conf_events_d2[i].end_time = 25000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "David J. Bianco");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Dan Holden & Elizabeth Martin");

    conf_events_d2[i].start_time = 25000;
    conf_events_d2[i].end_time = 31000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Break");

    conf_events_d2[i].start_time = 31000;
    conf_events_d2[i].end_time = 40000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "Joey Peloquin");
    b_strcpy(conf_events_d2[i++].ballroom_title, "David Sharpe & Katherine Trame");

    conf_events_d2[i].start_time = 40000;
    conf_events_d2[i].end_time = 41000;
    b_strcpy(conf_events_d2[i].other_title, "CTF!");
    b_strcpy(conf_events_d2[i].salon_title, "");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Break");

    conf_events_d2[i].start_time = 41000;
    conf_events_d2[i].end_time = 50000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Pete Herzog");

    conf_events_d2[i].start_time = 50000;
    conf_events_d2[i].end_time = 63000;
    b_strcpy(conf_events_d2[i].other_title, "\0");
    b_strcpy(conf_events_d2[i].salon_title, "\0");
    b_strcpy(conf_events_d2[i++].ballroom_title, "Reception at VCU");
}
/*
8:00	6:00	Registration
8:00	8:50	Breakfast sponsored by TruShield Security!
8:50	9:00	Welcome
9:00	10:00	Gene Fishel
Keynote
10:00	10:10	Break 	 	CTF
10:10	11:00	Evan Booth
Terminal Cornucopia: Demystifying the Mullet	  	CTF
11:00	11:10	Break 	 	CTF
11:10	12:00	Jonathan Dambrot
Third Party Risk Management and Cybersecurity	Steve Werby
Bad Advice, Unintended Consequences, and Broken Paradigms ? Think & Act Different!	CTF
12:00	1:00	Lunch 	 	CTF
1:00	1:50	Carmen Sullo & Kimberley Parsons
Leading Security When the Rest of The Business Doesn?t Care About Security	Ray Kelly
Man In The Front ? Modifying the Android OS for Mobile Application Testing	CTF
1:50	2:00	Break 	 	CTF
2:00	2:50	Dan Holden & Elizabeth Martin
Pissing Down The Leg Of Much Of Our Careers; Why Are You People Still Buying Firewalls & IPS?	David J. Bianco
The Pyramid of Pain: Intel-Driven Detection & Response to Increase Your Adversary?s Cost of Operations	CTF
2:50	3:10	Break 	 	CTF
3:10	4:00	David Sharpe & Katherine Trame
Real World Intrusion Response ? Lessons from the Trenches	Joey Peloquin
Offensive Mobile Forensics	CTF
4:00	4:10	Break 	 	CTF
4:10	5:00	Pete Herzog
Five Secrets to Building an Amazing Security Culture in Your Organization
5:00	6:30	Closing Reception (at VCU) sponsored by TruShield Security!
Prizes, CTF awards, beverages & Hors d?oeuvres

 */



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

