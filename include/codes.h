/*
** codes.h for MyIrc in /home/auzou_t/rendu/PSU_2014_myirc/include
** 
** Made by Thibaud Auzou
** Login   <auzou_t@epitech.net>
** 
** Started on  Sun Apr 12 18:36:13 2015 Thibaud Auzou
** Last update Sun Apr 12 18:36:42 2015 Thibaud Auzou
*/

#ifndef CODES_H_
# define CODES_H_

/*
** ERRORS
*/
# define E_421			":Unknown command"

# define E_431			":No nickname given"
# define E_432			":Erroneus nickname"
# define E_433			":Nickname is already in use"
# define E_461			":Not enough parameters"
# define E_462			":You may not reregister"
# define E_451			":You have not registered"
# define E_471			":Cannot join channel (+l)"
# define E_405			":You have joined too many channels"
# define E_403			":No such channel"
# define E_442			":You're not on that channel"
# define E_401			":No such nick/channel"
# define E_411			":No recipient given"
# define E_412			":No text to send"

/*
** RESPONSES
*/
# define R_001			":Welcome To MyIrc !"
# define R_002			":By Auzou_t & Montre_n !"
# define R_003			":Welcome To MyIrc !"
# define R_004			"V1 April 2015"
# define R_005			"%NaN% %NaN% %NaN% %NaN% %NaN%"
# define R_375			":- MyIrc Message of the Day -"
# define R_372			":- Coucou Twa ! LEL !"
# define R_376			":End of /MOTD command."
# define R_321			"Channel :Users  Name"
# define R_323			":End of /LIST"
# define R_366			":End of /NAMES list"

#endif /* !CODES_H_ */
