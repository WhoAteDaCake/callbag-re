open UtilsRe;

open TypeRe;

let fromList = (list, start, sink) =>
  switch start {
  | Start =>
    let completed = ref(false);
    let running = ref(false);
    whenTalk(sink, talk =>
      talk(
        Start,
        Talkback(
          (action, _data) =>
            switch action {
            | Start => ()
            | End => completed := true
            | Data =>
              if (! running^ && ! completed^) {
                running := true;
                Belt.List.forEach(list, item => talk(Data, Content(item)));
                talk(End, Nothing);
              }
            }
        )
      )
    );
  | _ => ()
  };