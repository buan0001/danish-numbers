
// // Write a function int_to_danish_word that takes an integet up to one billion as input and returns the Danish word for that number. The function should return NULL if the input is not a valid number. The function should return the Danish word in lowercase.

// // Example:
// // int_to_danish_word(1) should return "et"
// // int_to_danish_word(111) should return "et hundrede og elleve"
// // int_to_danish_word(1100000) should return "en million et hundrede tusinde"


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// void int_to_danish_word(int number, char* result);


// void int_to_danish_word(int number, char* result){
//     char* danish_words[] = {"nul", "et", "to", "tre", "fire", "fem", "seks", "syv", "otte", "ni", "ti", "elleve", "tolv", "tretten", "fjorten", "femten", "seksten", "sytten", "atten", "nitten", "tyve", "tredive", "fyrre", "halvtreds", "tres", "halvfjerds", "firs", "halvfems", "hundrede", "tusinde", "million", "milliard"};
   
//     if (number < 0 || number > 1000000000){
//         return NULL;
//     }
//     if (number == 0){
//         return danish_words[0];
//     }
//     int digits[10];
//     int i = 0;
//     while (number > 0){
//         digits[i] = number % 10;
//         number = number / 10;
//         i++;
//     }
//     int j = 0;
//     for (int k = i - 1; k >= 0; k--){
//         if (digits[k] != 0){
//             if (k == 0){
//                 strcat(result, danish_words[digits[k]]);
//             }
//             else if (k == 1){
//                 if (digits[k] == 1){
//                     strcat(result, danish_words[digits[k] * 10 + digits[k - 1]]);
//                     break;
//                 }
//                 else{
//                     strcat(result, danish_words[digits[k] + 18]);
//                 }
//             }
//             else{
//                 strcat(result, danish_words[digits[k]]);
//                 strcat(result, " ");
//                 strcat(result, danish_words[28 + k]);
//                 strcat(result, " ");
//             }
//         }
//     }

//     return;
// }