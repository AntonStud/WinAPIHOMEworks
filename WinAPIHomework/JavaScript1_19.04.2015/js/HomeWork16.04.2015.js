/**
 * Created by User on 16.04.2015.
 */

    var  quolities = ["Сильный","Смелый", "Добрый", "Умный"];

// Получаем элемент с id AddButton
var button = document.getElementById("AddButton");

var checkArr = document.getElementsByClassName("checkbox");

var CheckStates = function(){

    var tmp = "";

    for(var i = 0; i < checkArr.length; i++)
    {
        if(checkArr[i].checked) {

            tmp += quolities[i] + " ";

        }//  if(checkArr[i].checked) {

    }// for(var i = 0; i < checkArr.length; i++)

    return tmp;
};


var showMessage = function(){

    var result =  CheckStates();

    if(result.length){

    window.alert(result);

    }// if(result.length){

};// var showMessage = function(){

// Привязываем обработчик нажатия на кнопку
button.addEventListener("click", showMessage);
