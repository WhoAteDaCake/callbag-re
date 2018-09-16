open UtilsRe;

open TypeRe;

let take = (max, source, start, sink) => {
  let count = ref(0);
  let sourceTalkback = ref(Nothing);
  let talkback =
    Talkback(
      (action, data) =>
        if (count^ < max) {
          whenTalk(sourceTalkback^, talk => talk(action, data));
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
            whenTalk(sink, talk => talk(Start, talkback));
          | Data =>
            if (count^ === max) {
              whenTalk(sourceTalkback^, talk => talk(End, Nothing));
              whenTalk(sink, talk => talk(End, Nothing));
            } else {
              whenTalk(sink, talk => talk(action, data));
              count := count^ + 1;
            }
          | End => whenTalk(sink, talk => talk(action, data))
          }
      )
    )
  | _ => ()
  };
};