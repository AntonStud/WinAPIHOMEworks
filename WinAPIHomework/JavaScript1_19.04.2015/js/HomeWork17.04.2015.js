/**
 * Created by User on 16.04.2015.
 */

// Получаем элемент с id Select1
var select = document.getElementById("Select1");

// Функция для получения строки введенной пользователем для поиска в форму
var getTextFromInput = function(){
var text = document.getElementById('inp1').value;
//alert(text);
    return text;
};

// Функция для поиска подстроки в элементах options
var searchText = function(){
//Убираем выделения после предыдущего поиска
    select.selectedIndex = -1;
// Устанавливаем флаг найдено в ЛОЖЬ
    var flag = false;
// Получаем строку для сравнения
    var compare = getTextFromInput();
    // Если она не нулевой размерности запускаем поиск
    if(compare.length){

        // Проходим по массиву options элемента select
        for(var i = 0; i < select.length; i++) {

            // Если находит подстроку
            if (select.options[i].innerHTML.toLocaleLowerCase().indexOf(compare.toLocaleLowerCase())> -1)
            {
                //alert(select.options[i].innerHTML);
                //Подсвечиваем соответствующую строку в элементе
                select.options[i].selected = true;
                // Выставляем флаг найдено в ИСТИНУ
                flag = true;
                // Переходим на следующую строку
                continue;

            }//  if (select.options[i].innerHTML.indexOf(compare)> -1)

        }//  for(var i = 0; i < select.length; i++) {
    //Иначе выводим сообщение
    if(!flag) alert("Строка не найдена");
    }
};

// Получаем элемент с id AddButton
var button = document.getElementById("AddButton");

// Привязываем обработчик нажатия на кнопку
button.addEventListener("click", searchText);

