open UtilsRe;

open TypeRe;

let generateId = (start, sink) =>
  switch start {
  | Start =>
    let index = ref(-1);
    whenTalk(sink, talk =>
      talk(
        Start,
        Talkback(
          (action, _data) =>
            switch action {
            | Data =>
              index := index^ + 1;
              talk(Data, Content(index^));
            | _ => ()
            }
        )
      )
    );
  | _ => ()
  };