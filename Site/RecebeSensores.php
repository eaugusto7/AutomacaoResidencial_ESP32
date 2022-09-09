<?php
    include('conexao.php');
    
    $valor1 = $_GET['valor1'];
    $valor2 = $_GET['valor2'];
    $valor3 = $_GET['valor3'];

    $sql1 = "UPDATE Sensores  SET valor = :valor1 WHERE id = 0";
    $sql2 = "UPDATE Sensores  SET valor = :valor2 WHERE id = 1";
    $sql3 = "UPDATE Sensores  SET valor = :valor3 WHERE id = 2";
    
    $stmt = $PDO->prepare($sql1);
    $stmt->bindParam(':valor1',$valor1);
    if($stmt->execute()){echo "Valor 1 Salvo ";} 
    else{echo "Valor 1 Nao Salvo ";}

    $stmt = $PDO->prepare($sql2);
    $stmt->bindParam(':valor2',$valor2);
    if($stmt->execute()){echo "Valor 2 Salvo ";} 
    else{echo "Valor 2 Nao Salvo ";}
    
    $stmt = $PDO->prepare($sql3);
    $stmt->bindParam(':valor3',$valor3);
    if($stmt->execute()){echo "Valor Salvo ";} 
    else{echo "Valor 3 Nao Salvo ";}

?>