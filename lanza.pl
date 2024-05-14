#!/usr/bin/perl


#/***********************************
#Autores:
#- Leonardo Velázquez
#- Oscar Rodriguez
#- Nicolas Sanchez
#Fecha: 7 de mayo de 2024
#Materia: Sistemas Operativos
#Pontificia Universidad Javeriana
#Tema: Taller rendimiento
#*************************************/


$Path = `pwd`;
chomp($Path);

@Nombre_Ejecutable = ("MM_clasico","MM_transpuesta");
@Size_Matriz = ("200","400","800","1000","1500","2000", "2500", "4000");
@Num_Hilos = (1,2,4,6,8);
$Repeticiones = 30;

foreach $nombre (@Nombre_Ejecutable){
	foreach $size (@Size_Matriz){
		foreach $hilo (@Num_Hilos) {
			$file = "$Path/$nombre-".$size."-Hilos-".$hilo.".dat";
			for ($i=0; $i<$Repeticiones; $i++) {
			system("$Path/$nombre $size $hilo  >> $file");
			printf("$Path/$nombre $size $hilo \n");
		}
		close($file);
	$p=$p+1;
	}
	}
}
