interface Props {
  FooterColor: string;
  FooterText: string;
  TextColor: String;
}

const Footer = ({ FooterColor, FooterText, TextColor }: Props) => {
  return (
    <div>
      <footer
        className={
          `footer sm:footer-horizontal footer-center bg-${FooterColor} text-${TextColor}-content p-4 fixed bottom-0`
        }
      >
        <aside>
          <p>
            Copyright © {new Date().getFullYear()} - All right reserved by{" "}
            {FooterText}
          </p>
        </aside>
      </footer>
    </div>
  );
};

export default Footer;
