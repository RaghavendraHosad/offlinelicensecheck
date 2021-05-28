# offlinelicensecheck

A Simple COM based API for software features license check. 

There are many ways one can restrict access to their some of the core features of application or allow them to access on license based. Those who have valid license can only use those features.
This article brings a unique way to restrict software application features access. An ATL-COM based dll that comes with methods that enables application developers by calling COM dll methods, validates the license before the usage of those application features.

Flow Chart:

                                                                     ** START
                                                                        |
                                                                        V
                                                                  Check for .enc file
                                                                        |
                                                                        V
                                                         Decrypt .enc file and parse license.txt file
                                                                        |
                                                                        V
                                                         Check Expiry date & Last used Dt Vs Current system Dt
                                                                    | {Pass}            | {Fail}
                                                                    V                   V
                                                              Valid license      Fails validation
                                                              Update .enc               |
                                                                   |                    |
                                                                   ----------------------
                                                                             |
                                                                             V
                                                                            STOP**
  Project overview:
  
  1. OfflineLicenseMgmntTool - Project implemented in MFC (Dialog based) to edit license.txt file and to create .enc using openssl.exe
  2. LicenseOfflineCom - Project implemented using ATL/COM VC++ to implement license validity check
  3. WpfApplication - Project implemented using C# WPF, Is a client application uses ATL/COM dll to validate its license. (POC)
                                                                            
 The core functions are implemented as COM DLL, The client application that is developed using C#, VB, QT etc can simply import this DLL and can be used.
 in the POC C# .WPF application is calling this COM DLL to check validity.
