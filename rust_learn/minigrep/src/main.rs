use std::env;
use std::process;
use minigrep::Config;
fn main()
{
    
    let config = Config::build(env::args()).unwrap_or_else(|err|{
        eprintln!("你夏姬八输入什么了，不要喂食好吧");
        process::exit(1);
    });
    //let config = Config::new(&args);
    //let config = parse_config(&args);
    //let (query, file_path) = parse_config(&args);
    //dbg!(args);
    println!("{},{}",config.query,config.file_path);
    println!("");
    
    if let Err(e) = minigrep::run(config)
    {
        eprintln!("都说了不要夏姬八栾树如东西");
        process::exit(1);
    }
}
/*
fn run(config: Config)  -> Result<(), Box<dyn Error>>
{
    let contents = fs::read_to_string(config.file_path)?;


    println!("{contents}");
    Ok(())
}
struct Config
{
    query: String,
    file_path: String,
}
*/
/*
impl Config
{
    fn new(args: &[String]) -> Config
    {
        if args.len() < 3
        {
            panic!("你太小了");
        }
        let query = args[1].clone();
        let file_path =args[2].clone();

        Config {query,file_path}
    }
}
*/
/*
impl Config
{
    fn build(args: &[String]) -> Result<Config, &'static str>
    {
        if args.len() < 3
        {
            return Err("你太短了");
        }
        let query = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config{query, file_path})
    }
}*/
/*fn parse_config(args: &[String]) -> Config
{
    let query = args[1].clone();
    let file_path = args[2].clone();

    Config{query, file_path}
}*/