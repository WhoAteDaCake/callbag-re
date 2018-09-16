Callbag.(
  generateId
  |> filter(n => n mod 2 === 0)
  |> map(string_of_int)
  |> take(5)
  |> delay(100)
  |> forEach(a => Js.log(a))
);