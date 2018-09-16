open UtilsRe;

open TypeRe;

let fromLazyList = (list, start, sink) =>
  switch start {
  | Start =>
    let index = ref(0);
    let getNth = Belt.List.get(list);
    whenTalk(sink, talk =>
      talk(
        Start,
        Talkback(
          (action, _data) =>
            switch action {
            | Data =>
              switch (getNth(index^)) {
              | None => talk(End, Nothing)
              | Some(entry) =>
                /* Need to increase before callback, else can run out of stack frames */
                index := index^ + 1;
                talk(Data, Content(entry));
              }
            | _ => ()
            }
        )
      )
    );
  | _ => ()
  };