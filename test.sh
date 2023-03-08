#! /bin/bash

printf "\n\n\e[1;94m------Fclean and make CUBE------\e[0m\n"
make fclean
make
printf "\e[1;95m------Testing with test_map------\e[0m\n"
printf "\e[1;94m------should NOT OPEN------\e[0m\n\n"
./cub3d maps/test_map.cub
printf "\n\e[1;95m------Testing with test_ma.CUBORT------\e[0m\n"
printf "\e[1;94m------MAP DO NOT EXIST------\e[0m\n"
printf "\e[1;94m------should NOT OPEN------\e[0m\n\n"
./cub3d maps/test_map.cubORT
printf "\n\e[1;95m------Testing with test_map2.cub------\e[0m\n"
printf "\e[1;94m------problem with the texture------\e[0m\n"
printf "\e[1;94m------should NOT OPEN------\e[0m\n"
./cub3d maps/test_map2.cub
printf "\n\e[1;95m------Testing with test_map3.CAB------\e[0m\n"
printf "\e[1;94m------WRONG MAP NAME------\e[0m\n"
printf "\e[1;94m------should NOT OPEN------\e[0m\n\n"
./cub3d maps/test_map3.CAB
printf "\n\e[1;95m------Testing with test_map3.cub------\e[0m\n"
printf "\e[1;92m------should OPEN------\e[0m\n\n"
./cub3d maps/test_map3.cub
printf "\n\e[1;95m------Testing with test_map------\e[0m\n"
printf "\e[1;94m------should NOT OPEN------\e[0m\n\n"
./cub3d maps/test_map.cub
make fclean