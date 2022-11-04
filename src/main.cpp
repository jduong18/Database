#include <iostream>
#include <string>


# include "includes/SQL.hpp"


int main() {
    SQL sql;
    sql.run();

}


//The search function creatse a new table because the funcitonality right now is that when we want to select things, we will select things and put them
//into a new temp table to display, thats why there are versions on the search