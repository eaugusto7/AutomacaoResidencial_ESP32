
<?php
    try{
        $servername = "mysql.hostinger.com";
        $username = "user";
        $database = "db";
        $password = "password"; 
        
        $PDO = new PDO("mysql:host=".$servername.";dbname=".$database.";charset=utf8",$username,$password);
        
    }catch(PDOException $erro){
        
        echo "Erro ao conectar";
        echo $erro->getMessage();
    }
?>
