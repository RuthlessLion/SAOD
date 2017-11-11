package graphic

import (
	"fmt"
	"html/template"
	"net/http"
)

func indexHendler(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("graphic/test2.html")
	if err != nil {
		fmt.Fprint(w, "error index.html")
	}
	t.ExecuteTemplate(w, "index", nil)
}

func Init() {
	http.HandleFunc("/", indexHendler)
	http.Handle("/resourse/", http.StripPrefix("/resourse/", http.FileServer(http.Dir("./resourse/"))))
	err := http.ListenAndServe(":80", nil)
	if err != nil {
		fmt.Println("error listen: ", err)
	}
}
