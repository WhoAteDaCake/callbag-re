open UtilsRe;

open TypeRe;

let filter = (predicate, source, start, sink) => {
  let talkback = ref(Nothing);
  switch start {
  | Start =>
    source(
      Start,
      Talkback(
        (action, data) =>
          switch action {
          | Start =>
            talkback := data;
            whenTalk(sink, talk => talk(action, data));
          | Data =>
            switch data {
            | Content(body) =>
              if (predicate(body)) {
                whenTalk(sink, talk => talk(action, data));
              } else {
                whenTalk(talkback^, talk => talk(Data, Nothing));
              }
            | _ => ()
            }
          | End => whenTalk(sink, talk => talk(action, data))
          }
      )
    )
  | _ => ()
  };
};