// Получаем в массив все элементы с тэгом select
var selectTags = document.getElementsByTagName("select");

// Создаем два глобальных массива, в которых будет храниться
// информация
var arr1 =[];
var arr2 =[];

//Эта функция вносит значение в массив
// создает тег option и помещает его в соответствующий
// select
function addElement(someID, value, arr) {

    // Вносим в конец массива значение
        arr[arr.length] = value;

    // Создаем новый элемент с тегом option
        var option = document.createElement("option");

    // Заносим во внутренний HTML переданное значение
        option.innerHTML = value;

    // добавляем только что созданый элемент в дерево DOM
        var select = document.getElementById(someID);
        select.add(option);

}// function addElement(someID,start, iter, arr) {

// Заполняем массивы начальными значениями
var tmpStart = 1;
for(var i = 0; i < 5; i++){

    addElement(selectTags[0].getAttribute("id"), tmpStart++,  arr1);

}

tmpStart = 200;
for(var i = 0; i < 6; i++) {

    addElement(selectTags[1].getAttribute("id"), tmpStart++, arr2);

}
//----------------------------------------------------------------------
// Переменная для хранения id элемента
var flag;

// Привязываем обработчик фокуса соответствующего окна
selectTags[0].addEventListener("focus", function(){flag = selectTags[0].getAttribute("id");})
selectTags[1].addEventListener("focus", function(){flag = selectTags[1].getAttribute("id");})

// Получаем элемент с id AddButton
var button = document.getElementById("AddButton");

// Добавление следующей цифры, если одно из окон имеет фокус
var pushButton = function(){

    switch(flag){
        case selectTags[0].getAttribute("id"):

            addElement(flag, ++arr1[arr1.length - 1], arr1);

            break;

        case selectTags[1].getAttribute("id"):

            addElement(flag, ++arr2[arr2.length - 1], arr2);

            break;
    }//  switch(flag){

    flag = "";
};

// Привязываем обработчик нажатия на кнопку
button.addEventListener("click", pushButton);

