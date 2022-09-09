<?php
    include('conexao.php');

    if(in_array(0,$_POST["reles"]))$sql0="UPDATE Reles SET estado = 1 WHERE id = 0";
    else $sql0="UPDATE Reles SET estado = 0 WHERE id = 0";
    
    if(in_array(1,$_POST["reles"]))$sql1="UPDATE Reles SET estado = 1 WHERE id = 1";
    else $sql1="UPDATE Reles SET estado = 0 WHERE id = 1";

    if(in_array(2,$_POST["reles"]))$sql2="UPDATE Reles SET estado = 1 WHERE id = 2";
    else $sql2="UPDATE Reles SET estado = 0 WHERE id = 2";
    
    if(in_array(3,$_POST["reles"]))$sql3="UPDATE Reles SET estado = 1 WHERE id = 3";
    else $sql3="UPDATE Reles SET estado = 0 WHERE id = 3";
    
    $stmt = $PDO->prepare($sql0);
    if($stmt->execute()){ echo "Salvo0".'</br>';} 
    else{echo "Não salvo0".'</br>';}

    $stmt = $PDO->prepare($sql1);
    if($stmt->execute()){ echo "Salvo1".'</br>';} 
    else{echo "Não salvo1".'</br>';}
    
    $stmt = $PDO->prepare($sql2);
    if($stmt->execute()){ echo "Salvo2".'</br>';} 
    else{echo "Não salvo2".'</br>';}
    
    $stmt = $PDO->prepare($sql3);
    if($stmt->execute()){ echo "Salvo3".'</br>';} 
    else{echo "Não salvo3".'</br>';}

    header('Location: index.html'); 
?>