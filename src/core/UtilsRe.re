open TypeRe;

/* TODO improve naming of the functions as well as standartise them in a document*/
let whenTalk = (call, cb) =>
  switch call {
  | Talkback(fn) =>
    cb(fn);
    ();
  | _ => ()
  };

let whenContent = (call, cb) =>
  switch call {
  | Content(data) =>
    cb(data);
    ();
  | _ => ()
  };

let mapContent = (fn, content) =>
  switch content {
  | Content(data) => Content(fn(data))
  | _ => content
  };