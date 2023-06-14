// Hello world
function changeconten(){
    const prar = document.querySelector("p");
    prar.textContent = "Hello js."
    const css_file = document.querySelector("#css-a");
    css_file.setAttribute("href", "basic-b.css");
    
}

const button = document.getElementById("ch-button");


button.addEventListener("click", changeconten);