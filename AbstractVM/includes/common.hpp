#ifndef COMMOM_HPP
# define COMMOM_HPP

//Defines
# define DEBUG true

//Enumerations
enum class eInstruction { Push, Pop, Dump, Assert, Add, Sub, Mul, Div, Mod, Print, Exit, Unknown };
enum class eOperandType { Int8, Int16, Int32, Float, Double, Unknown };

#endif // COMMOM_HPP
