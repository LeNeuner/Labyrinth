/*!
\file
\brief Заголовочный файл, содержащий список с кодами ошибок
*/
#ifndef ERRORSLIST_H
#define ERRORSLIST_H

// General Errors
#define Success                             (0)
#define Incorrect_Parametr_Value            (-101)
#define Connection_Limit_Reached            (-102)
#define Cant_Check_Connection_Limit         (-103)
#define Connection_Already_Closed           (-104)

//File errors
#define File_Open_Failed                    (-400)
#define File_Format_Incorrect               (-401)
#define File_Size_Incorrect                 (-402)
#define Cant_Write_To_File                  (-403)

//Inner Errors
#define Inner_Error                         (-1000)

#endif // ERRORSLIST_H
