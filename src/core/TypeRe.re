type action =
  | Start
  | Data
  | End;

type callbag('a) = (action, payload('a)) => unit
and payload('a) =
  | Nothing
  | Content('a)
  | Talkback(callbag('a));