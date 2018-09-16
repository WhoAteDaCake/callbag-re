open UtilsRe;

open TypeRe;

let map = (operator: 'a => 'b, source, start, sink) => {
  let sourceTalkback = ref(Nothing);
  /* Currently can only send Nothing as data because of type system */
  let talkback =
    Talkback(
      (action, data) =>
        switch action {
        | End => whenTalk(sourceTalkback^, talk => talk(End, Nothing))
        | Data => whenTalk(sourceTalkback^, talk => talk(Data, Nothing))
        | _ => ()
        }
    );
  switch start {
  | Start =>
    source(
      Start,
      Talkback(
        (action, data) =>
          switch action {
          | Data =>
            switch data {
            | Content(body) =>
              let result: 'b = operator(body);
              whenTalk(sink, talk => talk(action, Content(result)));
            | _ => ()
            }
          | Start =>
            sourceTalkback := data;
            whenTalk(sink, talk => talk(Start, talkback));
          | End => whenTalk(sink, talk => talk(End, Nothing))
          }
      )
    )
  | _ => ()
  };
};