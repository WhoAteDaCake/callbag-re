open UtilsRe;

open TypeRe;

let delay = (time, source, start, sink) => {
  let sourceTalkback = ref(Nothing);
  let finished = ref(false);
  let timeout = ref(None);
  let talkback =
    Talkback(
      (action, data) =>
        switch action {
        | Data => whenTalk(sourceTalkback^, talk => talk(action, data))
        | End =>
          switch timeout^ {
          | Some(id) => Js.Global.clearTimeout(id)
          | None => ()
          };
          finished := true;
          whenTalk(sourceTalkback^, talk => talk(action, data));
        | Start => ()
        }
    );
  switch start {
  | Start =>
    source(
      Start,
      Talkback(
        (action, data) =>
          switch action {
          | Start =>
            sourceTalkback := data;
            whenTalk(sink, talk => talk(action, data));
          | Data =>
            timeout :=
              Some(
                Js.Global.setTimeout(
                  () =>
                    if (! finished^) {
                      whenTalk(sink, talk => talk(action, data));
                    },
                  time
                )
              )
          | End =>
            Js.Global.setTimeout(
              () => whenTalk(sink, talk => talk(End, Nothing)),
              time
            );
            ();
          }
      )
    )
  | _ => ()
  };
};