open UtilsRe;

open TypeRe;

let forEach = (operation, source) => {
  let talkback = ref(Nothing);
  source(
    Start,
    Talkback(
      (action, data) => {
        switch action {
        | Start => talkback := data
        | Data => whenContent(data, operation)
        | End => ()
        };
        switch action {
        | End => ()
        | _ => whenTalk(talkback^, talk => talk(Data, Nothing))
        };
      }
    )
  );
};